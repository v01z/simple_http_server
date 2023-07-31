#include <httpserver.hpp>
#include <iostream>
#include <fstream>

    using namespace httpserver;

    class hello_world_resource : public http_resource {
    public:
        std::shared_ptr<http_response> render(const http_request& request) {

            // Get info about client:
            std::cout << "\n******** Getting info about client: ********\n";
            std::cout << "\n\nGetting header:\n";
            std::map<std::string_view, std::string_view, http::header_comparator> headers =
                request.get_headers();
            for (const auto &elem : headers)
            {
                std::cout << elem.first << ": " << elem.second << std::endl;
            }

            std::cout << request.get_path() << std::endl;

            std::cout << "\n\nGetting content:\n";
            std::cout << request.get_content() << std::endl;

            std::cout << "\nClient's ip: " << request.get_requestor() << std::endl;
            std::cout << "\nClient's port: " << request.get_requestor_port() << std::endl;


            std::cout << "\n*********** End client info. ********\n\n";
            //End getting info about client

            //
            std::string filename { request.get_path() == "/"?"index.html":request.get_path().substr(1, request.get_path().length() - 1) };
            std::cout << "\nFilename is: " << filename << std::endl;

            std::string mime_str = filename == "index.html"?"text/html":"text/css";

            std::ifstream resource_file_stream(filename);
            //std::ifstream index_html("index.html");
            if(!resource_file_stream.is_open())
                return std::make_shared<httpserver::string_response>
                ( httpserver::string_response("Resource " + filename
                    + " not found.",
                     404, "text/plain"));
            
            std::stringstream buffer;
            buffer << resource_file_stream.rdbuf();
            resource_file_stream.close(); 

            //std::cout << buffer.rdbuf() << std::endl;

            buffer.seekg(0);

            return std::make_shared<httpserver::string_response>
                ( httpserver::string_response(buffer.rdbuf()->str(),
                    200, mime_str));

        }
    };

    int main(int argc, char** argv) {
        webserver ws { create_webserver(7070)  };

        hello_world_resource hwr;
        ws.register_resource("/", &hwr, true);
        ws.start(true);
        
        return 0;
    }