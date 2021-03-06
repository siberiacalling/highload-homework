#include "mime_types.hpp"

namespace http {
    namespace server3 {
        namespace mime_types {

            struct mapping {
                const char *extension;
                const char *mime_type;
            } mappings[] =
                    {
                            {"gif",  "image/gif"},
                            {"htm",  "text/html"},
                            {"html", "text/html"},
                            {"jpg",  "image/jpeg"},
                            {"jpeg",  "image/jpeg"},
                            {"png",  "image/png"},
                            {"css",  "text/css"},
                            {"js",  "text/javascript"},
                            {"swf",  "application/x-shockwave-flash"},
                            {0,      0} // Marks end of list.
                    };

            std::string extension_to_type(const std::string &extension) {
                for (mapping *m = mappings; m->extension; ++m) {
                    if (m->extension == extension) {
                        return m->mime_type;
                    }
                }

                return "text/plain";
            }

        } // namespace mime_types
    } // namespace server3
} // namespace http