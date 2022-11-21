#pragma once

#include <memory>
#include <stdexcept>
#include <string>

/*!
 * \brief Formats std::string in a similar way to snprintf
 *
 * Important: do not use std::string as a format argument.
 * Use std::string::c_string() method, and pass C-string instead.
 *
 * Source: https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 *
 * \param format the format string
 * \param args the formatting arguments
 * \return std::string of formatted text
 */
template<typename... Args>
std::string string_format(const std::string& format, Args... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if (size_s <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
