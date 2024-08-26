#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <sys/wait.h>
#include <unistd.h>

#include "version.hpp"

struct Out {
  int code;
  std::string out;
};

static Out my_popen(const std::string &cmd) {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    throw std::runtime_error("pipe failed");
  }
  pid_t pid = fork();
  if (0 == pid) {
    // child process

    close(pipefd[0]); // close read end
    dup2(pipefd[1], STDOUT_FILENO);
    dup2(pipefd[1], STDERR_FILENO);
    close(pipefd[1]); // close original write end of pipe

    execlp("/bin/bash", "bash", "-c", cmd.data(), (char *)0);

    // if execlp is successful, this code will not be executed
    throw std::runtime_error("failed to execute command in child process");

  } else if (0 < pid) {
    // parent process
    close(pipefd[1]); // Close the write end of the pipe
    FILE *pipe_stream = fdopen(pipefd[0], "r");
    if (!pipe_stream) {
      close(pipefd[0]);
      throw std::runtime_error("Failed to open pipe stream.");
    }

    Out result;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe_stream)) {
      result.out += buffer;
    }

    int status;
    waitpid(pid, &status, 0);
    result.code = status;
    fclose(pipe_stream);

    return result;

  } else {
    throw std::runtime_error("fork failed");
  }
}

static Out run(const std::string &cmd) { return my_popen(cmd); }

static void section(const std::string &cmd) {
  std::string piped_cmd = cmd + " 2>&1";

  std::cout << "==sysinfo== " << cmd << " ==sysinfo==\n";
  try {
    Out out = run(piped_cmd.data());
    if (out.code) {
      std::cout << "[NONZERO EXIT] " << out.code << std::endl;
    }
    std::cout << out.out << std::endl;
  } catch (std::runtime_error &e) {
    std::cout << "[INTERNAL ERROR] " << e.what() << std::endl;
  }
}

struct Cfg {
  bool version;
  bool help;
  Cfg() : version(false), help(false) {}
};

static Cfg parse_cli(int argc, char **argv) {
  Cfg cfg;
  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    if (arg == "-v" || arg == "--version") {
      cfg.version = true;
    } else if (arg == "-h" || arg == "--help") {
      cfg.help = true;
    }
  }
  return cfg;
}

const char *HELP_STR =
    R"(usage: sysinfo [OPTIONS]

optional arguments:
  -h, --help     show this help message and exit
  -v, --version  show program's version number and exit

This tool gathers and prints information about the system to standard out

The available flags are:

  -h, --help     Displays this help message and exits the program.
  -v, --version  Displays the version information of the program and exits.

Examples:
  sysinfo
  sysinfo -h
  sysinfo --help
  sysinfo -v
  sysinfo --version
)";

int main(int argc, char **argv) {

  Cfg cfg = parse_cli(argc, argv);

  if (cfg.help) {
    std::cout << HELP_STR;
    return 0;
  }

  if (cfg.version) {
    std::cout << "sysinfo " << SYSINFO_VERSION_MAJOR << "."
              << SYSINFO_VERSION_MINOR << "." << SYSINFO_VERSION_PATCH << "\n";
    return 0;
  }
  section("date");
  section("whoami");
  section("hostname");
  section("cmake --version");
  section("module list");
  section("uname -a");
#if defined(SYSINFO_ENABLE_LINUX)
  section("cat /etc/os-release");
  section("lscpu");
#elif defined(SYSINFO_ENABLE_DARWIN)
  section("sysctl -n machdep.cpu.brand_string");
  section("system_profiler SPHardwareDataType");
#endif
}