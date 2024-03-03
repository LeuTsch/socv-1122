#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <backends/cxxrtl/cxxrtl_vcd.h>
#include ".sim.cpp"
using namespace std;
 int main()
{
srand(time(NULL));unsigned random_value = 0;
unsigned upper_bound = 0;
char buffer[100];
vector<vector<unsigned>> stimulus_signal;
vector<unsigned> stimulus_cycle;
	std::ifstream ifs;
	ifs.open("./design/SoCV/vending/input-cex.pattern");
	for(size_t i = 0; i < 100000; ++i)
	{
		stimulus_cycle.clear();
		for(size_t j = 0; j < 5; ++j)
		{
			ifs >> buffer;
			stimulus_cycle.push_back(std::stoi(std::string(buffer)));
		}
		stimulus_signal.push_back(stimulus_cycle);
	}
	ifs.close();
ofstream ofs;
ofs.open("./design/SoCV/vending/output-cex.pattern");
     cxxrtl_design::p_vendingMachine top;
top.step();
for(int cycle=0;cycle<100000;++cycle){
top.p_clk.set<bool>(false);
top.step();
if(cycle == 0)
	top.p_reset.set<bool>(false);
else
	top.p_reset.set<bool>(true);
if(cycle > 0)
{
size_t idx = 0;
top.p_itemTypeIn.set<unsigned>(stimulus_signal[cycle][idx]);
++idx;
top.p_coinInNTD__1.set<unsigned>(stimulus_signal[cycle][idx]);
++idx;
top.p_coinInNTD__5.set<unsigned>(stimulus_signal[cycle][idx]);
++idx;
top.p_coinInNTD__10.set<unsigned>(stimulus_signal[cycle][idx]);
++idx;
top.p_coinInNTD__50.set<unsigned>(stimulus_signal[cycle][idx]);
++idx;
}
top.p_clk.set<bool>(true);
top.step();
uint32_t serviceTypeOut  = top.p_serviceTypeOut.get<uint32_t>();
uint32_t itemTypeOut  = top.p_itemTypeOut.get<uint32_t>();
uint32_t coinOutNTD_1  = top.p_coinOutNTD__1.get<uint32_t>();
uint32_t coinOutNTD_5  = top.p_coinOutNTD__5.get<uint32_t>();
uint32_t coinOutNTD_10  = top.p_coinOutNTD__10.get<uint32_t>();
uint32_t coinOutNTD_50  = top.p_coinOutNTD__50.get<uint32_t>();
uint32_t p  = top.p_p.get<uint32_t>();
uint32_t c  = top.p_c.get<uint32_t>();
uint32_t b  = top.p_b.get<uint32_t>();
uint32_t a  = top.p_a.get<uint32_t>();
ofs << "==========================================\n";
ofs << "= cycle " << cycle + 1 << "\n";
ofs << "==========================================\n";
ofs << "serviceTypeOut= " << serviceTypeOut << "\n";
ofs << "itemTypeOut= " << itemTypeOut << "\n";
ofs << "coinOutNTD_1= " << coinOutNTD_1 << "\n";
ofs << "coinOutNTD_5= " << coinOutNTD_5 << "\n";
ofs << "coinOutNTD_10= " << coinOutNTD_10 << "\n";
ofs << "coinOutNTD_50= " << coinOutNTD_50 << "\n";
ofs << "p= " << p << "\n";
ofs << "c= " << c << "\n";
ofs << "b= " << b << "\n";
ofs << "a= " << a << "\n";
}
ofs.close();
}

