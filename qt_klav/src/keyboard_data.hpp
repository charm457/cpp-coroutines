#pragma once

#include <vector>

#include "key_data.hpp"

namespace biv {
	class KeyBoardData {
		private:
			static const std::vector<KeyData> KEYS;

		public:
			std::vector<KeyData> get_line1() const;
			std::vector<KeyData> get_line2() const;
			std::vector<KeyData> get_line3() const;
			std::vector<KeyData> get_line4() const;
			
			bool is_key_allowed(const int code) const noexcept;
	};
}
