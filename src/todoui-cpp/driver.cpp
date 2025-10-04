#include <cstdlib>
#include <unordered_map>
#include <string>
#include <variant>

#include "crow.h"

int main(int argc, char *argv[]) {
  // set defaults
  using ConfigValT = std::variant<std::string, uint32_t>;
  std::unordered_map<std::string, ConfigValT> app_config={
          {"PORT", (uint32_t)8080},
          {"URL", "http://localhost:{}/todos/"}
  };

  // update URL
  app_config["URL"] = std::vformat(std::get<std::string>(app_config["URL"]),
		  std::make_format_args(
			  std::get<uint32_t>(app_config["PORT"])
			  ) 
		  );

  // update valued with environment
  {
    const char *pszEnvBackendURL = std::getenv("URL");
    if (pszEnvBackendURL != nullptr)
      app_config["URL"] = pszEnvBackendURL;
  }

  crow::SimpleApp app;
  CROW_ROUTE(app, "/")([](){
      auto page = crow::mustache::load("index.html");
      return page.render();
  });
  CROW_ROUTE(app, "/add").methods("POST"_method)(
    [](const crow::request& req){
      return crow::response{""};
  });
  CROW_ROUTE(app, "/delete").methods("POST"_method)(
    [](const crow::request& req){
      return crow::response{""};
  });

  app.port(std::get<uint32_t>(app_config["PORT"])).multithreaded().run();
  return 0;
}
