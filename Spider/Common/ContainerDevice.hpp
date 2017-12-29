//
// Created by Victor Debray on 07/10/2017.
//

#ifndef PROJECT_CONTAINERDEVICE_HPP
# define PROJECT_CONTAINERDEVICE_HPP

# include <algorithm>
# include <cassert>
# include <boost/config.hpp>
# include <boost/iostreams/categories.hpp>
# include <boost/iostreams/positioning.hpp>
# include <boost/iostreams/detail/ios.hpp>
# include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace spider
{
	namespace myboost
	{

		template<typename Container>
		class ContainerDevice
		{
		private:
			ContainerDevice operator=(const ContainerDevice &);
			typedef typename Container::size_type size_type;
			Container &container_;
			size_type pos_;

		public:
			typedef typename Container::value_type char_type;
			typedef boost::iostreams::seekable_device_tag category;

			explicit ContainerDevice(Container &container)
				: container_(container), pos_(0) {}

			std::streamsize read(char_type *s, std::streamsize n) {
				auto amt =
					static_cast<std::streamsize>(container_.size() - pos_);
				auto result = (std::min)(n, amt);
				if (result != 0) {
					std::copy(container_.begin() + pos_,
						container_.begin() + pos_ + result,
						s);
					pos_ += result;
					return result;
				} else {
					return -1; // EOF
				}
			}

			std::streamsize write(const char_type *s, std::streamsize n) {
				std::streamsize result = 0;
				if (pos_ != container_.size()) {
					std::streamsize amt =
						static_cast<std::streamsize>(container_.size() - pos_);
					result = (std::min)(n, amt);
					std::copy(s, s + result, container_.begin() + pos_);
					pos_ += result;
				}
				if (result < n) {
					container_.insert(container_.end(), s, s + n);
					pos_ = container_.size();
				}
				return n;
			}

			boost::iostreams::stream_offset seek(boost::iostreams::stream_offset off, BOOST_IOS::seekdir way) {
				// Determine new value of pos_
				boost::iostreams::stream_offset next;
				if (way == BOOST_IOS::beg) {
					next = off;
				} else if (way == BOOST_IOS::cur) {
					next = pos_ + off;
				} else if (way == BOOST_IOS::end) {
					next = container_.size() + off - 1;
				} else {
					throw BOOST_IOSTREAMS_FAILURE("bad seek direction");
				}

				if (next < (static_cast<boost::iostreams::stream_offset>(0))
					|| next >= (static_cast<boost::iostreams::stream_offset>(container_.size())))
					throw std::ios_base::failure("bad seek offset");

				pos_ = next;
				return pos_;
			}

			Container &container() { return container_; }
		};
	}
}


#endif //PROJECT_CONTAINERDEVICE_HPP
