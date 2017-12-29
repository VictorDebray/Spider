#pragma once

#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <AData.hpp>
#include "ADatabase.hpp"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class MongoConnector : public ADatabase<bsoncxx::document::view> {

  const std::string PROTOCOL = "mongodb://";

 public:
  MongoConnector(const std::string &address,
                 const std::string &port,
                 const std::string &databaseName);
  ~MongoConnector() override = default;

  void insertInDB(std::shared_ptr<spider::AData> data, spider::Type_e) override;


 private:
  mongocxx::instance instance{};
  std::shared_ptr<mongocxx::uri> uri_;
  std::shared_ptr<mongocxx::client> client_;
  std::shared_ptr<mongocxx::database> db_;
  std::shared_ptr<mongocxx::collection> coll_;
  bsoncxx::document::view currentView_;
  std::shared_ptr<spider::AData> currentData_;

  std::shared_ptr<bsoncxx::document::value> doc_value_;

  void checkAndCreateCollect();
  void buildBson(spider::Type_e e);
  void sendToDB();
  void handleQueue();

  void buildMouseLog();
  void buildInputLog();
};