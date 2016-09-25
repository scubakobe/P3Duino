#pragma once
#include "Connection.h"
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <SerialClass.h>
#include <msclr/marshal_cppstd.h>



#pragma pack(push, 1)
struct receiveData {
	char c;
	int32_t n;
};
#pragma pack(pop)

struct Data SimData;
receiveData receivedData;
bool serial_open = false;
bool serial_ready = false;


namespace P3DArduinoProgram {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::IO::Ports;
	using namespace System::Drawing;
	using namespace std;

	
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
		InitializeComponent();

		array<String^>^ serialPorts;
			try
			{
				serialPorts = serialArduino->GetPortNames();

			}
			catch (Win32Exception^ ex)
			{
				//Do something
			}

			for each(String^ port in serialPorts)
			{
				list_AvailPorts->Items->Add(String::Format(port));
			}
			
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  open_SimConnection;
	private: System::Windows::Forms::Button^  close_SimConnection;
	private: System::Windows::Forms::GroupBox^  group_P3DConnection;
	private: System::Windows::Forms::TextBox^  textbox_Altitude;
	private: System::Windows::Forms::Label^  label_Altitude;
	private: System::Windows::Forms::Timer^  timer_SimConnect;
	private: System::Windows::Forms::GroupBox^  group_Data;
	private: System::Windows::Forms::TextBox^  textbox_Airpseed;
	private: System::Windows::Forms::Label^  label_Airspeed;
	private: System::Windows::Forms::GroupBox^  group_ArduinoConnection;
	private: System::Windows::Forms::Button^  button_OpenArduino;
	private: System::Windows::Forms::Button^  button_CloseArduino;
	private: System::IO::Ports::SerialPort^  serialArduino;
	private: System::Windows::Forms::ComboBox^  combo_PortNum;
	private: System::Windows::Forms::Label^  label_ComPort;
	private: System::Windows::Forms::ListBox^  list_AvailPorts;
	private: System::Windows::Forms::Label^  label_AvailPorts;
	private: System::Windows::Forms::Timer^  timer_SerialData;
	private: System::Windows::Forms::TextBox^  textbox_baro;
	private: System::Windows::Forms::Label^  label_Kohlsmann;





	private: System::ComponentModel::IContainer^  components;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->open_SimConnection = (gcnew System::Windows::Forms::Button());
			this->close_SimConnection = (gcnew System::Windows::Forms::Button());
			this->group_P3DConnection = (gcnew System::Windows::Forms::GroupBox());
			this->textbox_Altitude = (gcnew System::Windows::Forms::TextBox());
			this->label_Altitude = (gcnew System::Windows::Forms::Label());
			this->timer_SimConnect = (gcnew System::Windows::Forms::Timer(this->components));
			this->group_Data = (gcnew System::Windows::Forms::GroupBox());
			this->textbox_Airpseed = (gcnew System::Windows::Forms::TextBox());
			this->label_Airspeed = (gcnew System::Windows::Forms::Label());
			this->group_ArduinoConnection = (gcnew System::Windows::Forms::GroupBox());
			this->label_AvailPorts = (gcnew System::Windows::Forms::Label());
			this->list_AvailPorts = (gcnew System::Windows::Forms::ListBox());
			this->label_ComPort = (gcnew System::Windows::Forms::Label());
			this->combo_PortNum = (gcnew System::Windows::Forms::ComboBox());
			this->button_OpenArduino = (gcnew System::Windows::Forms::Button());
			this->button_CloseArduino = (gcnew System::Windows::Forms::Button());
			this->serialArduino = (gcnew System::IO::Ports::SerialPort(this->components));
			this->timer_SerialData = (gcnew System::Windows::Forms::Timer(this->components));
			this->textbox_baro = (gcnew System::Windows::Forms::TextBox());
			this->label_Kohlsmann = (gcnew System::Windows::Forms::Label());
			this->group_P3DConnection->SuspendLayout();
			this->group_Data->SuspendLayout();
			this->group_ArduinoConnection->SuspendLayout();
			this->SuspendLayout();
			// 
			// open_SimConnection
			// 
			this->open_SimConnection->Location = System::Drawing::Point(6, 21);
			this->open_SimConnection->Name = L"open_SimConnection";
			this->open_SimConnection->Size = System::Drawing::Size(91, 23);
			this->open_SimConnection->TabIndex = 0;
			this->open_SimConnection->Text = L"Connect";
			this->open_SimConnection->UseVisualStyleBackColor = true;
			this->open_SimConnection->Click += gcnew System::EventHandler(this, &MainForm::open_SimConnection_Click);
			// 
			// close_SimConnection
			// 
			this->close_SimConnection->Location = System::Drawing::Point(103, 21);
			this->close_SimConnection->Name = L"close_SimConnection";
			this->close_SimConnection->Size = System::Drawing::Size(99, 23);
			this->close_SimConnection->TabIndex = 1;
			this->close_SimConnection->Text = L"Disconnect";
			this->close_SimConnection->UseVisualStyleBackColor = true;
			this->close_SimConnection->Click += gcnew System::EventHandler(this, &MainForm::close_SimConnection_Click);
			// 
			// group_P3DConnection
			// 
			this->group_P3DConnection->Controls->Add(this->open_SimConnection);
			this->group_P3DConnection->Controls->Add(this->close_SimConnection);
			this->group_P3DConnection->Location = System::Drawing::Point(12, 12);
			this->group_P3DConnection->Name = L"group_P3DConnection";
			this->group_P3DConnection->Size = System::Drawing::Size(208, 65);
			this->group_P3DConnection->TabIndex = 2;
			this->group_P3DConnection->TabStop = false;
			this->group_P3DConnection->Text = L"P3D Connection";
			// 
			// textbox_Altitude
			// 
			this->textbox_Altitude->Enabled = false;
			this->textbox_Altitude->Location = System::Drawing::Point(79, 21);
			this->textbox_Altitude->Name = L"textbox_Altitude";
			this->textbox_Altitude->Size = System::Drawing::Size(100, 22);
			this->textbox_Altitude->TabIndex = 3;
			this->textbox_Altitude->Text = L"0.00";
			// 
			// label_Altitude
			// 
			this->label_Altitude->AutoSize = true;
			this->label_Altitude->Location = System::Drawing::Point(9, 24);
			this->label_Altitude->Name = L"label_Altitude";
			this->label_Altitude->Size = System::Drawing::Size(55, 17);
			this->label_Altitude->TabIndex = 4;
			this->label_Altitude->Text = L"Altitude";
			// 
			// timer_SimConnect
			// 
			this->timer_SimConnect->Interval = 167;
			this->timer_SimConnect->Tick += gcnew System::EventHandler(this, &MainForm::timer_SimConnect_Tick);
			// 
			// group_Data
			// 
			this->group_Data->Controls->Add(this->textbox_baro);
			this->group_Data->Controls->Add(this->label_Kohlsmann);
			this->group_Data->Controls->Add(this->textbox_Airpseed);
			this->group_Data->Controls->Add(this->label_Airspeed);
			this->group_Data->Controls->Add(this->textbox_Altitude);
			this->group_Data->Controls->Add(this->label_Altitude);
			this->group_Data->Location = System::Drawing::Point(12, 83);
			this->group_Data->Name = L"group_Data";
			this->group_Data->Size = System::Drawing::Size(208, 210);
			this->group_Data->TabIndex = 3;
			this->group_Data->TabStop = false;
			this->group_Data->Text = L"Data";
			// 
			// textbox_Airpseed
			// 
			this->textbox_Airpseed->Enabled = false;
			this->textbox_Airpseed->Location = System::Drawing::Point(79, 49);
			this->textbox_Airpseed->Name = L"textbox_Airpseed";
			this->textbox_Airpseed->Size = System::Drawing::Size(100, 22);
			this->textbox_Airpseed->TabIndex = 5;
			this->textbox_Airpseed->Text = L"0.00";
			// 
			// label_Airspeed
			// 
			this->label_Airspeed->AutoSize = true;
			this->label_Airspeed->Location = System::Drawing::Point(9, 52);
			this->label_Airspeed->Name = L"label_Airspeed";
			this->label_Airspeed->Size = System::Drawing::Size(64, 17);
			this->label_Airspeed->TabIndex = 6;
			this->label_Airspeed->Text = L"Airspeed";
			// 
			// group_ArduinoConnection
			// 
			this->group_ArduinoConnection->Controls->Add(this->label_AvailPorts);
			this->group_ArduinoConnection->Controls->Add(this->list_AvailPorts);
			this->group_ArduinoConnection->Controls->Add(this->label_ComPort);
			this->group_ArduinoConnection->Controls->Add(this->combo_PortNum);
			this->group_ArduinoConnection->Controls->Add(this->button_OpenArduino);
			this->group_ArduinoConnection->Controls->Add(this->button_CloseArduino);
			this->group_ArduinoConnection->Location = System::Drawing::Point(226, 12);
			this->group_ArduinoConnection->Name = L"group_ArduinoConnection";
			this->group_ArduinoConnection->Size = System::Drawing::Size(208, 140);
			this->group_ArduinoConnection->TabIndex = 3;
			this->group_ArduinoConnection->TabStop = false;
			this->group_ArduinoConnection->Text = L"Arduino Connection";
			// 
			// label_AvailPorts
			// 
			this->label_AvailPorts->AutoSize = true;
			this->label_AvailPorts->Location = System::Drawing::Point(23, 92);
			this->label_AvailPorts->Name = L"label_AvailPorts";
			this->label_AvailPorts->Size = System::Drawing::Size(102, 17);
			this->label_AvailPorts->TabIndex = 9;
			this->label_AvailPorts->Text = L"Available Ports";
			// 
			// list_AvailPorts
			// 
			this->list_AvailPorts->FormattingEnabled = true;
			this->list_AvailPorts->ItemHeight = 16;
			this->list_AvailPorts->Location = System::Drawing::Point(131, 80);
			this->list_AvailPorts->Name = L"list_AvailPorts";
			this->list_AvailPorts->Size = System::Drawing::Size(71, 36);
			this->list_AvailPorts->TabIndex = 8;
			// 
			// label_ComPort
			// 
			this->label_ComPort->AutoSize = true;
			this->label_ComPort->Location = System::Drawing::Point(56, 53);
			this->label_ComPort->Name = L"label_ComPort";
			this->label_ComPort->Size = System::Drawing::Size(69, 17);
			this->label_ComPort->TabIndex = 7;
			this->label_ComPort->Text = L"COM Port";
			// 
			// combo_PortNum
			// 
			this->combo_PortNum->FormattingEnabled = true;
			this->combo_PortNum->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"COM1", L"COM2", L"COM3", L"COM4", L"COM5" });
			this->combo_PortNum->Location = System::Drawing::Point(131, 50);
			this->combo_PortNum->Name = L"combo_PortNum";
			this->combo_PortNum->Size = System::Drawing::Size(71, 24);
			this->combo_PortNum->TabIndex = 2;
			this->combo_PortNum->Text = L"COM1";
			// 
			// button_OpenArduino
			// 
			this->button_OpenArduino->Location = System::Drawing::Point(6, 21);
			this->button_OpenArduino->Name = L"button_OpenArduino";
			this->button_OpenArduino->Size = System::Drawing::Size(91, 23);
			this->button_OpenArduino->TabIndex = 0;
			this->button_OpenArduino->Text = L"Connect";
			this->button_OpenArduino->UseVisualStyleBackColor = true;
			this->button_OpenArduino->Click += gcnew System::EventHandler(this, &MainForm::button_OpenArduino_Click);
			// 
			// button_CloseArduino
			// 
			this->button_CloseArduino->Location = System::Drawing::Point(103, 21);
			this->button_CloseArduino->Name = L"button_CloseArduino";
			this->button_CloseArduino->Size = System::Drawing::Size(99, 23);
			this->button_CloseArduino->TabIndex = 1;
			this->button_CloseArduino->Text = L"Disconnect";
			this->button_CloseArduino->UseVisualStyleBackColor = true;
			this->button_CloseArduino->Click += gcnew System::EventHandler(this, &MainForm::button_CloseArduino_Click);
			// 
			// serialArduino
			// 
			this->serialArduino->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MainForm::serialArduino_DataReceived);
			// 
			// timer_SerialData
			// 
			this->timer_SerialData->Tick += gcnew System::EventHandler(this, &MainForm::timer_SerialData_Tick);
			// 
			// textbox_baro
			// 
			this->textbox_baro->Enabled = false;
			this->textbox_baro->Location = System::Drawing::Point(79, 77);
			this->textbox_baro->Name = L"textbox_baro";
			this->textbox_baro->Size = System::Drawing::Size(100, 22);
			this->textbox_baro->TabIndex = 7;
			this->textbox_baro->Text = L"0.00";
			// 
			// label_Kohlsmann
			// 
			this->label_Kohlsmann->AutoSize = true;
			this->label_Kohlsmann->Location = System::Drawing::Point(9, 80);
			this->label_Kohlsmann->Name = L"label_Kohlsmann";
			this->label_Kohlsmann->Size = System::Drawing::Size(38, 17);
			this->label_Kohlsmann->TabIndex = 8;
			this->label_Kohlsmann->Text = L"Baro";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(528, 427);
			this->Controls->Add(this->group_ArduinoConnection);
			this->Controls->Add(this->group_Data);
			this->Controls->Add(this->group_P3DConnection);
			this->Name = L"MainForm";
			this->Text = L"P3Duino";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->group_P3DConnection->ResumeLayout(false);
			this->group_Data->ResumeLayout(false);
			this->group_Data->PerformLayout();
			this->group_ArduinoConnection->ResumeLayout(false);
			this->group_ArduinoConnection->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void open_SimConnection_Click(System::Object^  sender, System::EventArgs^  e) {
		openSimConnection();
		timer_SimConnect->Start();
	}

	private: System::Void timer_SimConnect_Tick(System::Object^  sender, System::EventArgs^  e) {
		callSimConnect();
		//(Data*)&pObjData->dwData;
		memset(&SimData, 0, sizeof(struct Data));
		memcpy(&SimData, retrieveData(), sizeof(struct Data));
		textbox_Altitude->Text = SimData.altitude.ToString();
		textbox_baro->Text = SimData.kohlsmann.ToString();
	}
	private: System::Void close_SimConnection_Click(System::Object^  sender, System::EventArgs^  e) {
		timer_SimConnect->Stop();
	}
	private: System::Void button_OpenArduino_Click(System::Object^  sender, System::EventArgs^  e) {
		combo_PortNum->Enabled = false;
		serialArduino->PortName = combo_PortNum->Text;
		serialArduino->Open();
		serial_open = true;
		timer_SerialData->Start();
		
	}
	private: System::Void button_CloseArduino_Click(System::Object^  sender, System::EventArgs^  e) {
		timer_SerialData->Stop();
		combo_PortNum->Enabled = true;
		serialArduino->Close();
		serial_open = false;
		
	}
	private: System::Void timer_SerialData_Tick(System::Object^  sender, System::EventArgs^  e) {
		char buf[1024];
		float test;
		float kohls;
		sprintf(buf, "%f\n%f", SimData.altitude, SimData.kohlsmann);
		//cout << "Sending this: " << buf << "\n";
		sscanf(buf, "%f %f", &test, &kohls);
		//cout << "Found this: " << test << "\n" << kohls << "\n";
		String^ sendstr;
		sendstr = gcnew String(buf);
		//array<unsigned char>^ buffer = {4096};
		//serialArduino->Read(buffer, 0, sizeof(serialArduino->BytesToRead));
		serialArduino->WriteLine(sendstr);

	
		
	}
	private: System::Void serialArduino_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
		String^ incoming;
		const char *readData;
		incoming = serialArduino->ReadLine();

		std::string data = msclr::interop::marshal_as< std::string >(incoming);
		readData = data.c_str();
		std::cout << readData << "\n";

		//int size = serialArduino->BytesToRead;
		//array<unsigned char>^ buffer = { size + 1};
		//serialArduino->Read(buffer, 0, 0);
		//std::cout << buffer[0];

	}
};
}
