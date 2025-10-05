#include <cstdlib>
#include <unordered_map>
#include <string>
#include <variant>

#include "crow.h"
#include "cpr/cpr.h"

//template<typename T>
//const T& unmove(T&& t) {
//  return t;
//}

class LogHandler : public crow::ILogHandler
{
public:
    void log(const std::string& message, crow::LogLevel /*level*/) override
    {
        std::cerr << "LogHandler -> " << message;
    }
};

int main(int argc, char *argv[]) {
  // set defaults
  using ConfigValT = std::variant<std::string, uint32_t>;
  std::unordered_map<std::string, ConfigValT> app_config={
          {"FRONTEND_PORT", (uint32_t)5000},
//          {"BACKEND_PORT", (uint32_t)8080},
//          {"BACKEND_URL", "http://localhost{}/todos/"}
          {"BACKEND_URL", "http://localhost:8080/todos/"}
  };

  crow::logger::setLogLevel(crow::LogLevel::Debug);
  //crow::logger::setLogLevel(crow::LogLevel::Info);
  //crow::logger::setLogLevel(crow::LogLevel::Warning);

  //// update BACKEND_URL
  //if (app_config.contains("BACKEND_PORT")) {
  //  CROW_LOG_DEBUG << std::format("Debug | config BACKEND_URL: {}", std::get<uint32_t>(app_config["BACKEND_PORT"]));
//
  //  app_config["BACKEND_URL"] = std::vformat(std::get<std::string>(app_config["BACKEND_URL"]),
  //      std::make_format_args(
  //        unmove(std::string(":") += std::get<uint32_t>(app_config["BACKEND_PORT"]))
  //        )
  //      );
  //}

  // update with environment
  {
    const char *pszEnvFrontendPort = std::getenv("BACKEND_PORT");
    if (pszEnvFrontendPort != nullptr)
      app_config["FRONTEND_PORT"] = pszEnvFrontendPort;

    const char *pszEnvBackendURL = std::getenv("BACKEND_URL");
    if (pszEnvBackendURL != nullptr)
      app_config["BACKEND_URL"] = pszEnvBackendURL;
  }

  crow::SimpleApp app;

  CROW_ROUTE(app, "/")
  .methods("GET"_method)([&app_config](const crow::request& req){
      auto page = crow::mustache::load("index.html");
      CROW_LOG_INFO << std::format("GET {}/todos/", 
        std::get<std::string>(app_config["BACKEND_URL"])
      );

    auto cpr_resp = cpr::Get(cpr::Url{std::get<std::string>(app_config["BACKEND_URL"])});
    auto todos = crow::json::load(cpr_resp.text);
    //std::vector<crow::mustache::context> todos;
    //crow::mustache::context t1;
    //t1["todo"] = "Sample";
    //todos.push_back(std::move(t1));
    //crow::mustache::context ctx;
    //ctx["todos"] = std::move(todos);
    //return page.render(ctx);
    return page.render(todos);
  });

  CROW_ROUTE(app, "/add")
  .methods("POST"_method)([&app_config](const crow::request& req){
    crow::query_string qs = req.get_body_params();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Debug
    std::ostringstream oss;
    for (auto &key : qs.keys()) {
      oss << key << ": " << qs.get(key) << "\n";
    }
    CROW_LOG_DEBUG << oss.str();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    CROW_LOG_INFO << std::format("POST  {}/todos/{}",
        std::get<std::string>(app_config["BACKEND_URL"]), req.body
    );

    auto cpr_resp = cpr::Post(
        cpr::Url{std::get<std::string>(app_config["BACKEND_URL"])},
        cpr::Body{req.body},
        cpr::Header{{"Content-Type", "application/json"}}
    );
    CROW_LOG_DEBUG << "Add| CPR status code: " << cpr_resp.status_code << " CPR response: " << cpr_resp.text;

    crow::response resp;
    resp.redirect("/");
    return resp;
  });

  CROW_ROUTE(app, "/delete")
  .methods("POST"_method)([&app_config](const crow::request& req){
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Debug
    crow::multipart::message multi_req(req);
    std::ostringstream oss;
    for (auto &[key, part] : multi_req.part_map) {
      oss << key << ": " << part.body << "\n";
    }
    CROW_LOG_DEBUG << oss.str();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    auto delete_todo = multi_req.get_part_by_name("todo");
    CROW_LOG_INFO << std::format("POST  {}/todos/{}",
      std::get<std::string>(app_config["BACKEND_URL"]), delete_todo.body
    );
    //TODO integrate CPR
    auto cpr_resp = cpr::Post(
        cpr::Url{std::get<std::string>(app_config["BACKEND_URL"])},
        cpr::Body{delete_todo.body},
        cpr::Header{{"Content-Type", "application/json"}}
    );
    CROW_LOG_DEBUG << "Delete| CPR status code: " << cpr_resp.status_code << " CPR response: " << cpr_resp.text;

    crow::response resp;
    resp.redirect("/");
    return resp;
  });

  app.port(
    std::get<uint32_t>(app_config["FRONTEND_PORT"])
  ).multithreaded().run();

  return 0;
}
