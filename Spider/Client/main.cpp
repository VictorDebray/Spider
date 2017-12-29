#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "Client.hpp"
#include "FileManager.hpp"

std::string getID()
{
	std::string id;
	spider::client::FileManager	idSaver("spider.id");

	// Check if an ID already exists
	if (!idSaver.fileExists()) {
		// If not, generate a unique ID
		boost::uuids::uuid	uuid;

		uuid = boost::uuids::random_generator()();
		id = boost::lexical_cast<std::string>(uuid);

		// Register this ID
		idSaver.write(id);
	} else {
		id = idSaver.read();
	}

	return id;
}

int		main(int ac, char **av)
{
	try 
	{
		std::string id = getID();
		spider::client::Client client(id);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}