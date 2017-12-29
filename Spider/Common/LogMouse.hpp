#ifndef LOGMOUSE_HPP_
# define LOGMOUSE_HPP_

# include <boost/serialization/access.hpp>
# include <boost/serialization/base_object.hpp>
# include <string>

# include "AData.hpp"

namespace spider
{
class LogMouse : public AData
{
 protected:
  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int /*version*/)
  {
    ar & boost::serialization::base_object<AData>(*this);
    ar & windowName_;
    ar & windowSizeX_;
    ar & windowSizeY_;
    ar & mouseCoordX_;
    ar & mouseCoordY_;
  }

  std::string			windowName_;
  int					windowSizeX_;
  int					windowSizeY_;
  int					mouseCoordX_;
  int					mouseCoordY_;

 public:
  LogMouse() :
      AData(),
      windowName_(""),
      windowSizeX_(0),
      windowSizeY_(0),
      mouseCoordX_(0),
      mouseCoordY_(0)
  {}

  LogMouse(const std::string& id, int timeStamp, const std::string &windowName, const std::pair<int, int>& windowSize,
           const std::pair<int, int>& mouseCoord) :
      AData(id, timeStamp, LOGMOUSE),
      windowName_(windowName),
      windowSizeX_(windowSize.first),
      windowSizeY_(windowSize.second),
      mouseCoordX_(mouseCoord.first),
      mouseCoordY_(mouseCoord.second)
  {}

  ~LogMouse() override = default;
  void print();

  const std::string&			getWindowName() const { return (windowName_); }
  int	getWindowSizeX() const { return (windowSizeX_); }
  int	getWindowSizeY() const { return (windowSizeY_); }
  int	getMouseCoordX() const { return (mouseCoordX_); }
  int	getMouseCoordY() const { return (mouseCoordY_); }
};
}

#endif // !LOGMOUSE_HPP_