#include <cstdlib>
#include <unordered_map>
#include <string>

#include "crow.h"

int main(int argc, char *argv[]) {
  // set defaults
  std::unordered_map<std::string, std::string> app_config={{"BACKEND_URL", "http://localhost:8080/todos/"}};

  // update valued with environment
  {
    std::string sEnvironmentBackend = std::getenv("BACKEND_URL");
    if (!sEnvironmentBackend.empty())
      app_config["BACKEND_URL"] = sEnvironmentBackend;
  }

  crow::SimpleApp app;
  app.port(8080).multithreaded().run();
  return 0;
}
