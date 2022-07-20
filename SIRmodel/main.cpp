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

	susceptible = INITIAL_SUSCEPTIBLE; infected = INITIAL_INFECTED; recovered = INITIAL_RECOVERD;//�e�l���ɏ����l���i�[
	t = 0.0;

	file.open(fileName, ios::out);
	file << "time" << "," << "susceptible" << "," << "infected" << "," << "recovered" << endl;
	file << t << "," << susceptible << "," << infected << "," << recovered << endl;

	//4���̃����Q�E�N�b�^�@�ɂ�����������������
	while (t <= SIMULATION_TIME) {
		t += DELTA_T;

		//�����Q�E�N�b�^�@�̊e�i���̒l���Z�o����
		for (i = 0; i < 4; i++) {
			kS[i] = -INFECTION_RATE * susceptible * DELTA_T / 2 * (i + 1);
			kI[i] = ((INFECTION_RATE * susceptible) - (RECOVERY_RATE * infected)) * DELTA_T / 2 * (i + 1);
			kR[i] = RECOVERY_RATE * infected * DELTA_T / 2 * (i + 1);
		}

		//�d�ݕt�����ςɂ��A���̃X�e�b�v�̒l���Z�o����
		susceptible += (kS[0] + 2 * kS[1] + 2 * kS[2] + kS[3]) / 6;
		infected += (kI[0] + 2 * kI[1] + 2 * kI[2] + kI[3]) / 6;
		recovered += (kR[0] + 2 * kR[1] + 2 * kR[2] + kR[3]) / 6;

		//���ʂ��o��
		file << t << "," << susceptible << "," << infected << "," << recovered << endl;
	}
	
	file.close();

	return 0;
} 