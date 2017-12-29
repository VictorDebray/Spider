#pragma once

#include <iostream>
#include <queue>
#include <UsingClass.hpp>

template<class T>
class ADatabase {
 public:
  ADatabase(const std::string &address, const std::string &port, const std::string &databaseName)
      : address_(address), port_(port), databaseName_(databaseName) {}

  virtual ~ADatabase() = default;
  virtual void insertInDB(std::shared_ptr<spider::AData> data, spider::Type_e) = 0;

 protected:
  const std::string address_;
  const std::string port_;
  const std::string databaseName_;
  std::queue<T> cacheQueue_;
};
