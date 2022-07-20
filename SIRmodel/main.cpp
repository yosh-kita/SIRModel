#include <fstream>
#include <string>
#include "Parameter.h"

using namespace std;

int main() {
	int i;
	double susceptible, infected, recovered, t;
	double kS[4], kI[4], kR[4];
	ofstream file;
	string fileName="result.csv";

	susceptible = INITIAL_SUSCEPTIBLE; infected = INITIAL_INFECTED; recovered = INITIAL_RECOVERD;//各人口に初期値を格納
	t = 0.0;

	file.open(fileName, ios::out);
	file << "time" << "," << "susceptible" << "," << "infected" << "," << "recovered" << endl;
	file << t << "," << susceptible << "," << infected << "," << recovered << endl;

	//4次のルンゲ・クッタ法により微分方程式を解く
	while (t <= SIMULATION_TIME) {
		t += DELTA_T;

		//ルンゲ・クッタ法の各段数の値を算出する
		for (i = 0; i < 4; i++) {
			kS[i] = -INFECTION_RATE * susceptible * DELTA_T / 2 * (i + 1);
			kI[i] = ((INFECTION_RATE * susceptible) - (RECOVERY_RATE * infected)) * DELTA_T / 2 * (i + 1);
			kR[i] = RECOVERY_RATE * infected * DELTA_T / 2 * (i + 1);
		}

		//重み付け平均により、次のステップの値を算出する
		susceptible += (kS[0] + 2 * kS[1] + 2 * kS[2] + kS[3]) / 6;
		infected += (kI[0] + 2 * kI[1] + 2 * kI[2] + kI[3]) / 6;
		recovered += (kR[0] + 2 * kR[1] + 2 * kR[2] + kR[3]) / 6;

		//結果を出力
		file << t << "," << susceptible << "," << infected << "," << recovered << endl;
	}
	
	file.close();

	return 0;
} 