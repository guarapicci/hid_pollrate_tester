// hidapi pollrate.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

#include <hidapi.h>

#include <stdio.h>
#include <wchar.h>
#include <string>
#include <locale>

#include <chrono>
#include <thread>

#include <random>

#define MAX_STR 255

int main(int argc, char* argv[])
{
    using namespace std;
    cout << "hidapi poll rate tester\n";
    

    if ((argc != 3)) {
        cout << "please assign VID and PID as arguments.\n";
        return -1;
    }
    unsigned short VID = stoi(string(argv[1]), nullptr, 16);
    unsigned short PID = stoi(string(argv[2]), nullptr, 16);
    cout << "this test will attempt to poll for HID device (" << hex << (VID) << "):(" << hex << PID << dec << ").\n";

	int res;
	unsigned char buf[6000];
	wchar_t wstr[MAX_STR];
	hid_device* handle;
	int i;

	// Initialize the hidapi library
	res = hid_init();

	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open( VID, PID, NULL);
	if (!handle) {
		printf("Unable to open device\n");
		hid_exit();
		return 1;
	}

	// Read the Manufacturer String
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer String: %ls\n", wstr);

	// Read the Product String
	res = hid_get_product_string(handle, wstr, MAX_STR);
	printf("Product String: %ls\n", wstr);

	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	printf("Serial Number String: (%d) %ls\n", wstr[0], wstr);

	// Read Indexed String 1
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	printf("Indexed String 1: %ls\n", wstr);

	// Toggle LED (cmd 0x80). The first byte is the report number (0x0).
	buf[0] = 0x0;
	buf[1] = 0x80;
	res = hid_write(handle, buf, 6000);

	// Request state (cmd 0x81). The first byte is the report number (0x0).
	buf[0] = 0x0;
	buf[1] = 0x81;
	res = hid_write(handle, buf, 6000);

	// Read requested state
	res = hid_read(handle, buf, 6000);

	// Print out the returned buffer.
	for (i = 0; i < 4; i++)
		printf("buf[%d]: %d\n", i, buf[i]);

	cout << "TIMING CALIBRATION \n";
	cout << "\tdelay expected : 12ms\n";

	chrono::high_resolution_clock front_clock;
	for (int i = 0; i < 25; i++) {
		chrono::time_point<chrono::high_resolution_clock> before_sleep = front_clock.now();
		this_thread::sleep_for(chrono::milliseconds(12));
		chrono::time_point<chrono::high_resolution_clock> after_sleep = front_clock.now();
		chrono::duration<double, milli> total_sleep_time = (after_sleep - before_sleep);
		cout << "\treal readout " << i << ": " << total_sleep_time.count() << "ms\n";
	}

	cout << "a device has been detected. this program will now poll for 5000 input samples and dump their read time as microseconds.\n";

	chrono::high_resolution_clock the_timer;
	for (int i = 0;i < 5000;i++) {
		chrono::time_point<chrono::high_resolution_clock> before_read = the_timer.now();
		int bytes_read = hid_read(handle, buf, 60);
		chrono::time_point<chrono::high_resolution_clock> after_read = the_timer.now();
		chrono::duration<double, milli> interval = (after_read - before_read);
		// double chewed_up_frequency = 1 / (interval.count() / 1000);
		// if (chewed_up_frequency < 60) {
		// 	cout << "low poll rate! (" << chewed_up_frequency << "hz)" << std::endl;
		// }
		// cout << 1 / (interval.count() / 1000) << "hz,\n";

		if (bytes_read == 0)
			cout << "non-blocking: no hid data ready.\n";
		else {
			if (bytes_read == -1){
				cout << "hid read error. ";
				wstring hid_read_error(hid_error(handle));
				wcout << hid_read_error << L"\n";
				return -1;
			}
			else
				cout << interval.count() << "ms\n";
		}
	}
	// Close the device
	hid_close(handle);

	// Finalize the hidapi library
	res = hid_exit();

	return 0;
}

    


void timer_sample() {
    using namespace std;
    cout << "Hello World!\n";
    chrono::high_resolution_clock the_timer;

    //setup RNG to avoid the system optimizing away the print hard work.
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.


    for (int i = 0; i < 24; i++) {
        chrono::time_point<chrono::high_resolution_clock> before_print = the_timer.now();

        cout << "now printing some other stuff to console.\n";
        cout << gen() << "\n";
        chrono::time_point<chrono::high_resolution_clock> after_print = the_timer.now();
        cout.flush();

        chrono::duration<long long, nano> interval = (after_print - before_print);

        cout << "this print trio took " << (interval.count() / 1000) << " microseconds. \n";
        cout.flush();
    }

}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
