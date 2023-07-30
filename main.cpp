#include <httpserver.hpp>
#include <iostream>

    using namespace httpserver;

    class hello_world_resource : public http_resource {
    public:
        std::shared_ptr<http_response> render(const http_request& request) {

            // Get info about client:
            std::cout << "\n******** Getting info about client: ********\n";
            std::cout << "\n\nGetting header:\n";
            //std::map<std::string, std::string, http::header_comparator> headers =
            std::map<std::string_view, std::string_view, http::header_comparator> headers =
                request.get_headers();
            for (const auto &elem : headers)
            {
                std::cout << elem.first << ": " << elem.second << std::endl;
            }

            std::cout << "\n\nGetting content:\n";
            std::cout << request.get_content() << std::endl;

            std::cout << "\nClient's ip: " << request.get_requestor() << std::endl;
            std::cout << "\nClient's port: " << request.get_requestor_port() << std::endl;


            std::cout << "\n*********** End client info. ********\n\n";
            //End getting info about client

            return std::shared_ptr<http_response>(new string_response("Hello, World!"));
        }
    };

    int main(int argc, char** argv) {
        webserver ws = create_webserver(7070);

        hello_world_resource hwr;
        ws.register_resource("/hello", &hwr);
        ws.start(true);
        
        return 0;
    }