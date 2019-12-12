#include <iostream>

#include "toumasulo.h"
#include "Parser.h"

int main() {

    std::string prog_file_name = "program.txt";
    std::cout << "enter text file containing assembly program" << std::endl;
    std::cin >> prog_file_name;

    Parser parse(prog_file_name);

    std::string mem_file_name;
    std::cout << std::endl << "enter text file containing memory" << std::endl;
    std::cin >> mem_file_name;

    std::cout << std::endl << "enter custom hardware parameters?" << std::endl << "[y/n]";
    char in;
    std::cin >> in;

    int issues = 2, max_rob = 2, l_s = 2, s_s = 2, j_s = 2, b_s = 2, a_s = 3, n_s = 2, m_s = 2, l_c = 3, s_c = 3, j_c = 1, b_c = 1, a_c = 2, n_c = 1, m_c = 10;

    if (in == 'y' || in == 'Y') {
        std::cout << std::endl << std::endl << "enter number of issues";
        std::cin >> issues;
        std::cout << std::endl << std::endl << "enter number of ROB entries";
        std::cin >> max_rob;

        std::cout << std::endl << std::endl << "enter number of load units";
        std::cin >> l_s;
        std::cout << std::endl << std::endl << "enter number of save units";
        std::cin >> s_s;
        std::cout << std::endl << std::endl << "enter number of jump units";
        std::cin >> j_s;
        std::cout << std::endl << std::endl << "enter number of branch units";
        std::cin >> b_s;
        std::cout << std::endl << std::endl << "enter number of add units";
        std::cin >> a_s;
        std::cout << std::endl << std::endl << "enter number of nand units";
        std::cin >> n_s;
        std::cout << std::endl << std::endl << "enter number of multiplication units";
        std::cin >> m_s;

        std::cout << std::endl << std::endl << "enter number of load execute cycles";
        std::cin >> l_c;
        std::cout << std::endl << std::endl << "enter number of store execute cycles";
        std::cin >> s_c;
        std::cout << std::endl << std::endl << "enter number of jump execute cycles";
        std::cin >> j_c;
        std::cout << std::endl << std::endl << "enter number of branch execute cycles";
        std::cin >> b_c;
        std::cout << std::endl << std::endl << "enter number of add execute cycles";
        std::cin >> a_c;
        std::cout << std::endl << std::endl << "enter number of nand execute cycles";
        std::cin >> n_c;
        std::cout << std::endl << std::endl << "enter number of multiplication execute cycles";
        std::cin >> m_c;
    }

    toumasulo data_path(mem_file_name, issues, max_rob, l_s, s_s, j_s, b_s, a_s, n_s, m_s, l_c, s_c, j_c, b_c, a_c, n_c, m_c);

    data_path.get_inst(parse.Get_Instructions());

    while (!data_path.adv_c()) {}

    int i;
    float ipc, branch;
    data_path.get_results(i, ipc, branch);

    std::cout << "total cycles: " << i << std::endl << "IPC: " << ipc << std::endl << "branch prediction accuracy: ";
    if (branch == -1) {
        std::cout << "no branches in program";
    } else {
        cout << branch;
    }

    return 0;
}