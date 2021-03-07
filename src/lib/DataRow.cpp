#include "DataRow.h"

namespace SQLCore {

    DataRow::DataRow(uint32_t uniqueId, const std::string &username, const std::string &email) : d_id(uniqueId),
                                                                                                 d_username(username),
                                                                                                 d_email(email) {

    }

    DataRow::operator std::string() const {
        return "(" + std::to_string(d_id) + ", " + d_username + ", " + d_email + ")";
    }

}