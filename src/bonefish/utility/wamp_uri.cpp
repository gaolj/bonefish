/**
 *  Copyright (C) 2015 Topology LP
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <bonefish/utility/wamp_uri.hpp>
#include <regex>

namespace bonefish {

namespace uri_flags {
unsigned int allow_empty_components = 1;
unsigned int strict = 1 << 1;
} // namespace uri_flags

bool is_valid_uri(const std::string& uri, int flags)
{
    if (flags & uri_flags::allow_empty_components) {
        if (flags & uri_flags::strict) {
            static std::regex strict_uri_regex_empty("^(([0-9a-z_]+\\.)|\\.)*([0-9a-z_]+)?$",
                    std::regex_constants::nosubs | std::regex_constants::optimize);

            return std::regex_match(uri, strict_uri_regex_empty);
        }

        static std::regex relaxed_uri_regex_empty("^(([^\\s\\.#]+\\.)|\\.)*([^\\s\\.#]+)?$",
                std::regex_constants::nosubs | std::regex_constants::optimize);

        return std::regex_match(uri, relaxed_uri_regex_empty);
    }

    if (flags & uri_flags::strict) {
        static std::regex strict_uri_regex("^([0-9a-z_]+\\.)*([0-9a-z_]+)$",
                std::regex_constants::nosubs | std::regex_constants::optimize);

        return std::regex_match(uri, strict_uri_regex);
    }

    static std::regex relaxed_uri_regex("^([^\\s\\.#]+\\.)*([^\\s\\.#]+)$",
            std::regex_constants::nosubs | std::regex_constants::optimize);

    return std::regex_match(uri, relaxed_uri_regex);
}

} // namespace bonefish
