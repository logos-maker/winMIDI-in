
#include <windows.h> 
#include <stdbool.h> 

#include <stdio.h>
#include <conio.h>
#include <wchar.h>

void PrintMidiDevices()
{
	UINT nMidiDeviceNum;
	MIDIINCAPS incaps;
	MIDIOUTCAPS outcaps;

	nMidiDeviceNum = midiInGetNumDevs();
	if (nMidiDeviceNum == 0) {
		fprintf(stderr, "midiInGetNumDevs() return 0...");
		return;
	}

	printf("MIDI input devices:\n");
	for (unsigned int i = 0; i < midiInGetNumDevs(); i++) {
		midiInGetDevCaps(i, &incaps, sizeof(MIDIINCAPS));
		wprintf(L"    %d : name = %s\n", i, incaps.szPname);
	}

	printf("MIDI output devices:\n");
	for (unsigned int i = 0; i < midiOutGetNumDevs(); i++) {
		midiOutGetDevCaps(i, &outcaps, sizeof(MIDIINCAPS));
		wprintf(L"    %d : name = %s\n", i, outcaps.szPname);
	}

	printf("\n");
}

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2){

	if(wMsg==MIM_DATA ) {

		union { 
			DWORD dwData; 
			BYTE data[4]; 
		} midi;

		midi.dwData = dwParam1;

		printf("BYTE 0:  0x%hhX,  BYTE 1:  0x%hhX,  BYTE 3: 0x%hhX \n",midi.data[0],midi.data[1],midi.data[2] );
	}
	return;
}

int main(int argc, char* argv[])
{
	HMIDIIN hMidiDevice = NULL;;
	DWORD nMidiPort = 0;
	UINT nMidiDeviceNum;
	MMRESULT rv;

	PrintMidiDevices();

	nMidiDeviceNum = midiInGetNumDevs();
	if (nMidiDeviceNum == 0) {
		fprintf(stderr, "midiInGetNumDevs() zero devices found...");
		return -1;
	}

	rv = midiInOpen(&hMidiDevice, nMidiPort, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION);

	if (rv != MMSYSERR_NOERROR) {
		fprintf(stderr, "midiInOpen() failed to open MIDI... rv=%d", rv);
		return -1;
	}

	midiInStart(hMidiDevice);

	while (true) {
		if (!_kbhit()) {
			Sleep(100);
			continue;
		}
		int c = _getch();
		if (c == 'q') break; // press q to quit CMD application
	}

	midiInStop(hMidiDevice);
	midiInClose(hMidiDevice);
	hMidiDevice = NULL;

	return 0;
}