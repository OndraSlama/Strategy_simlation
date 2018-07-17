#pragma once
#include "Structs.h"
#include "StrategyB.h"
#include "StrategyC.h"
#include "Motors.h"

#include "Global.h"
#include "ExtraMath.h"
#include "PhyShapes.h"
#include "Board.h"

#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <ctime>


namespace StrategyGUISimulator {

	using namespace System;
	using namespace System::Windows;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	//	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{

	public:

		Form1();
		~Form1();
		void buttonStart_Click(Object^, EventArgs^);
		void pictureBox1_Paint(System::Object^, System::Windows::Forms::PaintEventArgs^);
		void MoveAxis();
		void timerMain_Tick(Object^, EventArgs^);
		void timerCamera_Tick();
		void SetupAxis();
		void SimType_CheckedChanged(Object^, EventArgs^);
		void buttonStop_Click(Object^, EventArgs^);
		void TeamCount_CheckedChanged(Object^, EventArgs^);
		void PauseCont_Click(Object^, EventArgs^);
		void UpdateGUI();
		String^ StrategyModeEnumToString(int);
		String^ AxisModeEnumToString(int);
		void StartStaticSimulation();
		void StartDynamicSimulation();

	private: System::ComponentModel::IContainer^  components;


			 array<Axis*>^ player1axes = gcnew array<Axis*>(4);
			 array<Axis*>^ player2axes = gcnew array<Axis*>(4);

			 Ball* ball = new Ball;
			 Sim * sim;

			 int cameraError;
			 int cameraFPS;
			 int cameraInterval;
			 int cyclesToCameraCycle;

			 BaseStrategy* strategy1;
			 BaseStrategy* strategy2;
			 int DummyX = 120; // X
			 int DummyY = 210; // Y
			 int ballRadius = 175;
			 int maxAcc = 3;
			 int TimeZoom;

	private: System::Windows::Forms::Timer^  timerMain;
	private: System::Drawing::Graphics^ g;
	private: System::Windows::Forms::Button^  buttonStart;


	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TextBox^  PosX;
	private: System::Windows::Forms::TextBox^  PosY;


	private: System::Windows::Forms::TextBox^  VelX;
	private: System::Windows::Forms::TextBox^  VelY;


	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::RadioButton^  staticS;
	private: System::Windows::Forms::Button^  buttonStop;

	private: System::Windows::Forms::RadioButton^  oneTeam;
	private: System::Windows::Forms::RadioButton^  twoTeams;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  PauseCont;

	private: System::Windows::Forms::TextBox^  tbxFPS;




	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  tbxMode1;
	private: System::Windows::Forms::Label^  goalkeeper;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  tbxA1Y;
	private: System::Windows::Forms::TextBox^  tbxA2Y;
	private: System::Windows::Forms::TextBox^  tbxA3Y;
	private: System::Windows::Forms::TextBox^  tbxA4Y;
	private: System::Windows::Forms::TextBox^  tbxA1desP;
	private: System::Windows::Forms::TextBox^  tbxA2desP;
	private: System::Windows::Forms::TextBox^  tbxA3desP;
	private: System::Windows::Forms::TextBox^  tbxA4desP;
	private: System::Windows::Forms::TextBox^  tbxA1mode;
	private: System::Windows::Forms::TextBox^  tbxA2mode;
	private: System::Windows::Forms::TextBox^  tbxA3mode;
	private: System::Windows::Forms::TextBox^  tbxA4mode;
	private: System::Windows::Forms::TextBox^  tbxA4mode2;
	private: System::Windows::Forms::TextBox^  tbxA4desP2;


	private: System::Windows::Forms::TextBox^  tbxA4Y2;
	private: System::Windows::Forms::TextBox^  tbxA3mode2;
	private: System::Windows::Forms::TextBox^  tbxA3desP2;



	private: System::Windows::Forms::TextBox^  tbxA3Y2;
	private: System::Windows::Forms::TextBox^  tbxA2mode2;
	private: System::Windows::Forms::TextBox^  tbxA2desP2;



	private: System::Windows::Forms::TextBox^  tbxA2Y2;
private: System::Windows::Forms::TextBox^  tbxA1mode2;
private: System::Windows::Forms::TextBox^  tbxA1desP2;



private: System::Windows::Forms::TextBox^  tbxA1Y2;

	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;




private: System::Windows::Forms::TextBox^  tbxMode2;

	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label21;

private: System::Windows::Forms::ListBox^  StrategyListBox1;
private: System::Windows::Forms::ListBox^  StrategyListBox2;
private: System::Windows::Forms::TextBox^  tbxA4init;
private: System::Windows::Forms::TextBox^  tbxA3init;
private: System::Windows::Forms::TextBox^  tbxA2init;
private: System::Windows::Forms::TextBox^  tbxA1init;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::TextBox^  tbxA4init2;
private: System::Windows::Forms::TextBox^  tbxA3init2;
private: System::Windows::Forms::TextBox^  tbxA2init2;
private: System::Windows::Forms::TextBox^  tbxA1init2;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::Label^  label27;

private: System::Windows::Forms::Label^  label28;

private: System::Windows::Forms::TextBox^  tbxCameraError;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label3;
















private: System::Windows::Forms::Panel^  panel3;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::TextBox^  tbxTimeZoom;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::TextBox^  ballCurrentVelocityY;
private: System::Windows::Forms::TextBox^  ballCurrentVelocityX;
private: System::Windows::Forms::TextBox^  ballCurrentPositionY;
private: System::Windows::Forms::TextBox^  ballCurrentPositionX;



	private: System::Windows::Forms::RadioButton^  dynamicS;





#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->buttonStart = (gcnew System::Windows::Forms::Button());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->timerMain = (gcnew System::Windows::Forms::Timer(this->components));
				 this->PosX = (gcnew System::Windows::Forms::TextBox());
				 this->PosY = (gcnew System::Windows::Forms::TextBox());
				 this->VelX = (gcnew System::Windows::Forms::TextBox());
				 this->VelY = (gcnew System::Windows::Forms::TextBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->staticS = (gcnew System::Windows::Forms::RadioButton());
				 this->dynamicS = (gcnew System::Windows::Forms::RadioButton());
				 this->buttonStop = (gcnew System::Windows::Forms::Button());
				 this->oneTeam = (gcnew System::Windows::Forms::RadioButton());
				 this->twoTeams = (gcnew System::Windows::Forms::RadioButton());
				 this->panel1 = (gcnew System::Windows::Forms::Panel());
				 this->panel2 = (gcnew System::Windows::Forms::Panel());
				 this->PauseCont = (gcnew System::Windows::Forms::Button());
				 this->tbxFPS = (gcnew System::Windows::Forms::TextBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->tbxMode1 = (gcnew System::Windows::Forms::TextBox());
				 this->goalkeeper = (gcnew System::Windows::Forms::Label());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->label10 = (gcnew System::Windows::Forms::Label());
				 this->label11 = (gcnew System::Windows::Forms::Label());
				 this->label12 = (gcnew System::Windows::Forms::Label());
				 this->tbxA1Y = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2Y = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3Y = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA4Y = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA1desP = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2desP = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3desP = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA4desP = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA1mode = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2mode = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3mode = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA4mode = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA4mode2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA4desP2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA4Y2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3mode2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3desP2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3Y2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2mode2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2desP2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2Y2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA1mode2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA1desP2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA1Y2 = (gcnew System::Windows::Forms::TextBox());
				 this->label13 = (gcnew System::Windows::Forms::Label());
				 this->label14 = (gcnew System::Windows::Forms::Label());
				 this->label15 = (gcnew System::Windows::Forms::Label());
				 this->tbxMode2 = (gcnew System::Windows::Forms::TextBox());
				 this->label20 = (gcnew System::Windows::Forms::Label());
				 this->label21 = (gcnew System::Windows::Forms::Label());
				 this->StrategyListBox1 = (gcnew System::Windows::Forms::ListBox());
				 this->StrategyListBox2 = (gcnew System::Windows::Forms::ListBox());
				 this->tbxA4init = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3init = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2init = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA1init = (gcnew System::Windows::Forms::TextBox());
				 this->label22 = (gcnew System::Windows::Forms::Label());
				 this->tbxA4init2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA3init2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA2init2 = (gcnew System::Windows::Forms::TextBox());
				 this->tbxA1init2 = (gcnew System::Windows::Forms::TextBox());
				 this->label23 = (gcnew System::Windows::Forms::Label());
				 this->label24 = (gcnew System::Windows::Forms::Label());
				 this->label25 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->label26 = (gcnew System::Windows::Forms::Label());
				 this->label27 = (gcnew System::Windows::Forms::Label());
				 this->label28 = (gcnew System::Windows::Forms::Label());
				 this->tbxCameraError = (gcnew System::Windows::Forms::TextBox());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->label16 = (gcnew System::Windows::Forms::Label());
				 this->label17 = (gcnew System::Windows::Forms::Label());
				 this->label18 = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->panel3 = (gcnew System::Windows::Forms::Panel());
				 this->label19 = (gcnew System::Windows::Forms::Label());
				 this->label36 = (gcnew System::Windows::Forms::Label());
				 this->tbxTimeZoom = (gcnew System::Windows::Forms::TextBox());
				 this->label37 = (gcnew System::Windows::Forms::Label());
				 this->label29 = (gcnew System::Windows::Forms::Label());
				 this->label30 = (gcnew System::Windows::Forms::Label());
				 this->label31 = (gcnew System::Windows::Forms::Label());
				 this->label32 = (gcnew System::Windows::Forms::Label());
				 this->label33 = (gcnew System::Windows::Forms::Label());
				 this->label34 = (gcnew System::Windows::Forms::Label());
				 this->ballCurrentVelocityY = (gcnew System::Windows::Forms::TextBox());
				 this->ballCurrentVelocityX = (gcnew System::Windows::Forms::TextBox());
				 this->ballCurrentPositionY = (gcnew System::Windows::Forms::TextBox());
				 this->ballCurrentPositionX = (gcnew System::Windows::Forms::TextBox());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 this->panel1->SuspendLayout();
				 this->panel2->SuspendLayout();
				 this->panel3->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // buttonStart
				 // 
				 this->buttonStart->Location = System::Drawing::Point(28, 12);
				 this->buttonStart->Name = L"buttonStart";
				 this->buttonStart->Size = System::Drawing::Size(195, 50);
				 this->buttonStart->TabIndex = 0;
				 this->buttonStart->Text = L"Start";
				 this->buttonStart->UseVisualStyleBackColor = true;
				 this->buttonStart->Click += gcnew System::EventHandler(this, &Form1::buttonStart_Click);
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->BackColor = System::Drawing::Color::White;
				 this->pictureBox1->Location = System::Drawing::Point(252, 11);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(1210, 703);
				 this->pictureBox1->TabIndex = 1;
				 this->pictureBox1->TabStop = false;
				 this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox1_Paint);
				 // 
				 // timerMain
				 // 
				 this->timerMain->Interval = 50;
				 this->timerMain->Tick += gcnew System::EventHandler(this, &Form1::timerMain_Tick);
				 // 
				 // PosX
				 // 
				 this->PosX->Location = System::Drawing::Point(83, 41);
				 this->PosX->Name = L"PosX";
				 this->PosX->Size = System::Drawing::Size(76, 20);
				 this->PosX->TabIndex = 2;
				 this->PosX->Text = L"6500";
				 // 
				 // PosY
				 // 
				 this->PosY->Location = System::Drawing::Point(83, 67);
				 this->PosY->Name = L"PosY";
				 this->PosY->Size = System::Drawing::Size(76, 20);
				 this->PosY->TabIndex = 3;
				 this->PosY->Text = L"600";
				 // 
				 // VelX
				 // 
				 this->VelX->Location = System::Drawing::Point(82, 129);
				 this->VelX->Name = L"VelX";
				 this->VelX->Size = System::Drawing::Size(76, 20);
				 this->VelX->TabIndex = 4;
				 this->VelX->Text = L"-10";
				 // 
				 // VelY
				 // 
				 this->VelY->Location = System::Drawing::Point(80, 155);
				 this->VelY->Name = L"VelY";
				 this->VelY->Size = System::Drawing::Size(78, 20);
				 this->VelY->TabIndex = 5;
				 this->VelY->Text = L"2";
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label1->Location = System::Drawing::Point(12, 13);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(173, 25);
				 this->label1->TabIndex = 6;
				 this->label1->Text = L"Ball Initial Position:";
				 // 
				 // staticS
				 // 
				 this->staticS->AutoSize = true;
				 this->staticS->Location = System::Drawing::Point(16, 3);
				 this->staticS->Name = L"staticS";
				 this->staticS->Size = System::Drawing::Size(68, 17);
				 this->staticS->TabIndex = 8;
				 this->staticS->Text = L"static sim";
				 this->staticS->UseVisualStyleBackColor = true;
				 this->staticS->CheckedChanged += gcnew System::EventHandler(this, &Form1::SimType_CheckedChanged);
				 // 
				 // dynamicS
				 // 
				 this->dynamicS->AutoSize = true;
				 this->dynamicS->Checked = true;
				 this->dynamicS->Location = System::Drawing::Point(16, 26);
				 this->dynamicS->Name = L"dynamicS";
				 this->dynamicS->Size = System::Drawing::Size(82, 17);
				 this->dynamicS->TabIndex = 9;
				 this->dynamicS->TabStop = true;
				 this->dynamicS->Text = L"dynamic sim";
				 this->dynamicS->UseVisualStyleBackColor = true;
				 this->dynamicS->CheckedChanged += gcnew System::EventHandler(this, &Form1::SimType_CheckedChanged);
				 // 
				 // buttonStop
				 // 
				 this->buttonStop->Location = System::Drawing::Point(28, 82);
				 this->buttonStop->Name = L"buttonStop";
				 this->buttonStop->Size = System::Drawing::Size(195, 50);
				 this->buttonStop->TabIndex = 10;
				 this->buttonStop->Text = L"Stop";
				 this->buttonStop->UseVisualStyleBackColor = true;
				 this->buttonStop->Click += gcnew System::EventHandler(this, &Form1::buttonStop_Click);
				 // 
				 // oneTeam
				 // 
				 this->oneTeam->AutoSize = true;
				 this->oneTeam->Location = System::Drawing::Point(16, 3);
				 this->oneTeam->Name = L"oneTeam";
				 this->oneTeam->Size = System::Drawing::Size(69, 17);
				 this->oneTeam->TabIndex = 11;
				 this->oneTeam->Text = L"one team";
				 this->oneTeam->UseVisualStyleBackColor = true;
				 this->oneTeam->CheckedChanged += gcnew System::EventHandler(this, &Form1::TeamCount_CheckedChanged);
				 // 
				 // twoTeams
				 // 
				 this->twoTeams->AutoSize = true;
				 this->twoTeams->Checked = true;
				 this->twoTeams->Location = System::Drawing::Point(16, 26);
				 this->twoTeams->Name = L"twoTeams";
				 this->twoTeams->Size = System::Drawing::Size(73, 17);
				 this->twoTeams->TabIndex = 12;
				 this->twoTeams->TabStop = true;
				 this->twoTeams->Text = L"two teams";
				 this->twoTeams->UseVisualStyleBackColor = true;
				 this->twoTeams->CheckedChanged += gcnew System::EventHandler(this, &Form1::TeamCount_CheckedChanged);
				 // 
				 // panel1
				 // 
				 this->panel1->Controls->Add(this->twoTeams);
				 this->panel1->Controls->Add(this->oneTeam);
				 this->panel1->Location = System::Drawing::Point(131, 442);
				 this->panel1->Name = L"panel1";
				 this->panel1->Size = System::Drawing::Size(102, 54);
				 this->panel1->TabIndex = 13;
				 // 
				 // panel2
				 // 
				 this->panel2->Controls->Add(this->staticS);
				 this->panel2->Controls->Add(this->dynamicS);
				 this->panel2->Location = System::Drawing::Point(12, 442);
				 this->panel2->Name = L"panel2";
				 this->panel2->Size = System::Drawing::Size(108, 54);
				 this->panel2->TabIndex = 14;
				 // 
				 // PauseCont
				 // 
				 this->PauseCont->Location = System::Drawing::Point(28, 152);
				 this->PauseCont->Name = L"PauseCont";
				 this->PauseCont->Size = System::Drawing::Size(195, 50);
				 this->PauseCont->TabIndex = 15;
				 this->PauseCont->Text = L"Pause";
				 this->PauseCont->UseVisualStyleBackColor = true;
				 this->PauseCont->Click += gcnew System::EventHandler(this, &Form1::PauseCont_Click);
				 // 
				 // tbxFPS
				 // 
				 this->tbxFPS->Location = System::Drawing::Point(104, 557);
				 this->tbxFPS->Name = L"tbxFPS";
				 this->tbxFPS->Size = System::Drawing::Size(100, 20);
				 this->tbxFPS->TabIndex = 16;
				 this->tbxFPS->Text = L"40";
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(33, 702);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(53, 13);
				 this->label4->TabIndex = 20;
				 this->label4->Text = L"strategy 1";
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(33, 782);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(36, 13);
				 this->label5->TabIndex = 21;
				 this->label5->Text = L"mode:";
				 // 
				 // tbxMode1
				 // 
				 this->tbxMode1->Location = System::Drawing::Point(34, 798);
				 this->tbxMode1->Name = L"tbxMode1";
				 this->tbxMode1->Size = System::Drawing::Size(100, 20);
				 this->tbxMode1->TabIndex = 22;
				 // 
				 // goalkeeper
				 // 
				 this->goalkeeper->AutoSize = true;
				 this->goalkeeper->Location = System::Drawing::Point(153, 728);
				 this->goalkeeper->Name = L"goalkeeper";
				 this->goalkeeper->Size = System::Drawing::Size(60, 13);
				 this->goalkeeper->TabIndex = 23;
				 this->goalkeeper->Text = L"goalkeeper";
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(153, 751);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(49, 13);
				 this->label7->TabIndex = 23;
				 this->label7->Text = L"defender";
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(153, 776);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(51, 13);
				 this->label8->TabIndex = 23;
				 this->label8->Text = L"midfielder";
				 // 
				 // label9
				 // 
				 this->label9->AutoSize = true;
				 this->label9->Location = System::Drawing::Point(153, 803);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(42, 13);
				 this->label9->TabIndex = 23;
				 this->label9->Text = L"forward";
				 // 
				 // label10
				 // 
				 this->label10->AutoSize = true;
				 this->label10->Location = System::Drawing::Point(219, 829);
				 this->label10->Name = L"label10";
				 this->label10->Size = System::Drawing::Size(14, 13);
				 this->label10->TabIndex = 23;
				 this->label10->Text = L"Y";
				 // 
				 // label11
				 // 
				 this->label11->AutoSize = true;
				 this->label11->Location = System::Drawing::Point(336, 829);
				 this->label11->Name = L"label11";
				 this->label11->Size = System::Drawing::Size(33, 13);
				 this->label11->TabIndex = 23;
				 this->label11->Text = L"mode";
				 // 
				 // label12
				 // 
				 this->label12->AutoSize = true;
				 this->label12->Location = System::Drawing::Point(423, 829);
				 this->label12->Name = L"label12";
				 this->label12->Size = System::Drawing::Size(80, 13);
				 this->label12->TabIndex = 23;
				 this->label12->Text = L"desired position";
				 // 
				 // tbxA1Y
				 // 
				 this->tbxA1Y->Location = System::Drawing::Point(215, 722);
				 this->tbxA1Y->Name = L"tbxA1Y";
				 this->tbxA1Y->Size = System::Drawing::Size(78, 20);
				 this->tbxA1Y->TabIndex = 24;
				 // 
				 // tbxA2Y
				 // 
				 this->tbxA2Y->Location = System::Drawing::Point(214, 750);
				 this->tbxA2Y->Name = L"tbxA2Y";
				 this->tbxA2Y->Size = System::Drawing::Size(78, 20);
				 this->tbxA2Y->TabIndex = 24;
				 // 
				 // tbxA3Y
				 // 
				 this->tbxA3Y->Location = System::Drawing::Point(214, 776);
				 this->tbxA3Y->Name = L"tbxA3Y";
				 this->tbxA3Y->Size = System::Drawing::Size(78, 20);
				 this->tbxA3Y->TabIndex = 24;
				 // 
				 // tbxA4Y
				 // 
				 this->tbxA4Y->Location = System::Drawing::Point(214, 802);
				 this->tbxA4Y->Name = L"tbxA4Y";
				 this->tbxA4Y->Size = System::Drawing::Size(78, 20);
				 this->tbxA4Y->TabIndex = 24;
				 // 
				 // tbxA1desP
				 // 
				 this->tbxA1desP->Location = System::Drawing::Point(425, 721);
				 this->tbxA1desP->Name = L"tbxA1desP";
				 this->tbxA1desP->Size = System::Drawing::Size(78, 20);
				 this->tbxA1desP->TabIndex = 24;
				 // 
				 // tbxA2desP
				 // 
				 this->tbxA2desP->Location = System::Drawing::Point(424, 749);
				 this->tbxA2desP->Name = L"tbxA2desP";
				 this->tbxA2desP->Size = System::Drawing::Size(78, 20);
				 this->tbxA2desP->TabIndex = 24;
				 // 
				 // tbxA3desP
				 // 
				 this->tbxA3desP->Location = System::Drawing::Point(424, 775);
				 this->tbxA3desP->Name = L"tbxA3desP";
				 this->tbxA3desP->Size = System::Drawing::Size(78, 20);
				 this->tbxA3desP->TabIndex = 24;
				 // 
				 // tbxA4desP
				 // 
				 this->tbxA4desP->Location = System::Drawing::Point(424, 801);
				 this->tbxA4desP->Name = L"tbxA4desP";
				 this->tbxA4desP->Size = System::Drawing::Size(78, 20);
				 this->tbxA4desP->TabIndex = 24;
				 // 
				 // tbxA1mode
				 // 
				 this->tbxA1mode->Location = System::Drawing::Point(320, 721);
				 this->tbxA1mode->Name = L"tbxA1mode";
				 this->tbxA1mode->Size = System::Drawing::Size(78, 20);
				 this->tbxA1mode->TabIndex = 24;
				 // 
				 // tbxA2mode
				 // 
				 this->tbxA2mode->Location = System::Drawing::Point(319, 749);
				 this->tbxA2mode->Name = L"tbxA2mode";
				 this->tbxA2mode->Size = System::Drawing::Size(78, 20);
				 this->tbxA2mode->TabIndex = 24;
				 // 
				 // tbxA3mode
				 // 
				 this->tbxA3mode->Location = System::Drawing::Point(319, 775);
				 this->tbxA3mode->Name = L"tbxA3mode";
				 this->tbxA3mode->Size = System::Drawing::Size(78, 20);
				 this->tbxA3mode->TabIndex = 24;
				 // 
				 // tbxA4mode
				 // 
				 this->tbxA4mode->Location = System::Drawing::Point(319, 801);
				 this->tbxA4mode->Name = L"tbxA4mode";
				 this->tbxA4mode->Size = System::Drawing::Size(78, 20);
				 this->tbxA4mode->TabIndex = 24;
				 // 
				 // tbxA4mode2
				 // 
				 this->tbxA4mode2->Location = System::Drawing::Point(1094, 801);
				 this->tbxA4mode2->Name = L"tbxA4mode2";
				 this->tbxA4mode2->Size = System::Drawing::Size(78, 20);
				 this->tbxA4mode2->TabIndex = 47;
				 // 
				 // tbxA4desP2
				 // 
				 this->tbxA4desP2->Location = System::Drawing::Point(1199, 801);
				 this->tbxA4desP2->Name = L"tbxA4desP2";
				 this->tbxA4desP2->Size = System::Drawing::Size(78, 20);
				 this->tbxA4desP2->TabIndex = 45;
				 // 
				 // tbxA4Y2
				 // 
				 this->tbxA4Y2->Location = System::Drawing::Point(989, 802);
				 this->tbxA4Y2->Name = L"tbxA4Y2";
				 this->tbxA4Y2->Size = System::Drawing::Size(78, 20);
				 this->tbxA4Y2->TabIndex = 44;
				 // 
				 // tbxA3mode2
				 // 
				 this->tbxA3mode2->Location = System::Drawing::Point(1094, 775);
				 this->tbxA3mode2->Name = L"tbxA3mode2";
				 this->tbxA3mode2->Size = System::Drawing::Size(78, 20);
				 this->tbxA3mode2->TabIndex = 43;
				 // 
				 // tbxA3desP2
				 // 
				 this->tbxA3desP2->Location = System::Drawing::Point(1199, 775);
				 this->tbxA3desP2->Name = L"tbxA3desP2";
				 this->tbxA3desP2->Size = System::Drawing::Size(78, 20);
				 this->tbxA3desP2->TabIndex = 42;
				 // 
				 // tbxA3Y2
				 // 
				 this->tbxA3Y2->Location = System::Drawing::Point(989, 776);
				 this->tbxA3Y2->Name = L"tbxA3Y2";
				 this->tbxA3Y2->Size = System::Drawing::Size(78, 20);
				 this->tbxA3Y2->TabIndex = 41;
				 // 
				 // tbxA2mode2
				 // 
				 this->tbxA2mode2->Location = System::Drawing::Point(1094, 749);
				 this->tbxA2mode2->Name = L"tbxA2mode2";
				 this->tbxA2mode2->Size = System::Drawing::Size(78, 20);
				 this->tbxA2mode2->TabIndex = 40;
				 // 
				 // tbxA2desP2
				 // 
				 this->tbxA2desP2->Location = System::Drawing::Point(1199, 749);
				 this->tbxA2desP2->Name = L"tbxA2desP2";
				 this->tbxA2desP2->Size = System::Drawing::Size(78, 20);
				 this->tbxA2desP2->TabIndex = 39;
				 // 
				 // tbxA2Y2
				 // 
				 this->tbxA2Y2->Location = System::Drawing::Point(989, 750);
				 this->tbxA2Y2->Name = L"tbxA2Y2";
				 this->tbxA2Y2->Size = System::Drawing::Size(78, 20);
				 this->tbxA2Y2->TabIndex = 38;
				 // 
				 // tbxA1mode2
				 // 
				 this->tbxA1mode2->Location = System::Drawing::Point(1095, 721);
				 this->tbxA1mode2->Name = L"tbxA1mode2";
				 this->tbxA1mode2->Size = System::Drawing::Size(78, 20);
				 this->tbxA1mode2->TabIndex = 37;
				 // 
				 // tbxA1desP2
				 // 
				 this->tbxA1desP2->Location = System::Drawing::Point(1200, 721);
				 this->tbxA1desP2->Name = L"tbxA1desP2";
				 this->tbxA1desP2->Size = System::Drawing::Size(78, 20);
				 this->tbxA1desP2->TabIndex = 46;
				 // 
				 // tbxA1Y2
				 // 
				 this->tbxA1Y2->Location = System::Drawing::Point(990, 722);
				 this->tbxA1Y2->Name = L"tbxA1Y2";
				 this->tbxA1Y2->Size = System::Drawing::Size(78, 20);
				 this->tbxA1Y2->TabIndex = 36;
				 // 
				 // label13
				 // 
				 this->label13->AutoSize = true;
				 this->label13->Location = System::Drawing::Point(1198, 829);
				 this->label13->Name = L"label13";
				 this->label13->Size = System::Drawing::Size(80, 13);
				 this->label13->TabIndex = 35;
				 this->label13->Text = L"desired position";
				 // 
				 // label14
				 // 
				 this->label14->AutoSize = true;
				 this->label14->Location = System::Drawing::Point(1111, 829);
				 this->label14->Name = L"label14";
				 this->label14->Size = System::Drawing::Size(33, 13);
				 this->label14->TabIndex = 34;
				 this->label14->Text = L"mode";
				 // 
				 // label15
				 // 
				 this->label15->AutoSize = true;
				 this->label15->Location = System::Drawing::Point(994, 829);
				 this->label15->Name = L"label15";
				 this->label15->Size = System::Drawing::Size(14, 13);
				 this->label15->TabIndex = 33;
				 this->label15->Text = L"Y";
				 // 
				 // tbxMode2
				 // 
				 this->tbxMode2->Location = System::Drawing::Point(1432, 820);
				 this->tbxMode2->Name = L"tbxMode2";
				 this->tbxMode2->Size = System::Drawing::Size(100, 20);
				 this->tbxMode2->TabIndex = 28;
				 // 
				 // label20
				 // 
				 this->label20->AutoSize = true;
				 this->label20->Location = System::Drawing::Point(1431, 804);
				 this->label20->Name = L"label20";
				 this->label20->Size = System::Drawing::Size(36, 13);
				 this->label20->TabIndex = 27;
				 this->label20->Text = L"mode:";
				 // 
				 // label21
				 // 
				 this->label21->AutoSize = true;
				 this->label21->Location = System::Drawing::Point(1429, 720);
				 this->label21->Name = L"label21";
				 this->label21->Size = System::Drawing::Size(53, 13);
				 this->label21->TabIndex = 26;
				 this->label21->Text = L"strategy 2";
				 // 
				 // StrategyListBox1
				 // 
				 this->StrategyListBox1->FormattingEnabled = true;
				 this->StrategyListBox1->Location = System::Drawing::Point(34, 721);
				 this->StrategyListBox1->Name = L"StrategyListBox1";
				 this->StrategyListBox1->Size = System::Drawing::Size(100, 56);
				 this->StrategyListBox1->TabIndex = 48;
				 // 
				 // StrategyListBox2
				 // 
				 this->StrategyListBox2->FormattingEnabled = true;
				 this->StrategyListBox2->Location = System::Drawing::Point(1432, 740);
				 this->StrategyListBox2->Name = L"StrategyListBox2";
				 this->StrategyListBox2->Size = System::Drawing::Size(100, 56);
				 this->StrategyListBox2->TabIndex = 49;
				 // 
				 // tbxA4init
				 // 
				 this->tbxA4init->Location = System::Drawing::Point(569, 801);
				 this->tbxA4init->Name = L"tbxA4init";
				 this->tbxA4init->Size = System::Drawing::Size(78, 20);
				 this->tbxA4init->TabIndex = 51;
				 this->tbxA4init->Text = L"0";
				 // 
				 // tbxA3init
				 // 
				 this->tbxA3init->Location = System::Drawing::Point(569, 775);
				 this->tbxA3init->Name = L"tbxA3init";
				 this->tbxA3init->Size = System::Drawing::Size(78, 20);
				 this->tbxA3init->TabIndex = 52;
				 this->tbxA3init->Text = L"0";
				 // 
				 // tbxA2init
				 // 
				 this->tbxA2init->Location = System::Drawing::Point(569, 749);
				 this->tbxA2init->Name = L"tbxA2init";
				 this->tbxA2init->Size = System::Drawing::Size(78, 20);
				 this->tbxA2init->TabIndex = 53;
				 this->tbxA2init->Text = L"0";
				 // 
				 // tbxA1init
				 // 
				 this->tbxA1init->Location = System::Drawing::Point(570, 721);
				 this->tbxA1init->Name = L"tbxA1init";
				 this->tbxA1init->Size = System::Drawing::Size(78, 20);
				 this->tbxA1init->TabIndex = 54;
				 this->tbxA1init->Text = L"0";
				 // 
				 // label22
				 // 
				 this->label22->AutoSize = true;
				 this->label22->Location = System::Drawing::Point(568, 829);
				 this->label22->Name = L"label22";
				 this->label22->Size = System::Drawing::Size(69, 13);
				 this->label22->TabIndex = 50;
				 this->label22->Text = L"initial position";
				 // 
				 // tbxA4init2
				 // 
				 this->tbxA4init2->Location = System::Drawing::Point(1328, 805);
				 this->tbxA4init2->Name = L"tbxA4init2";
				 this->tbxA4init2->Size = System::Drawing::Size(78, 20);
				 this->tbxA4init2->TabIndex = 56;
				 this->tbxA4init2->Text = L"0";
				 // 
				 // tbxA3init2
				 // 
				 this->tbxA3init2->Location = System::Drawing::Point(1328, 779);
				 this->tbxA3init2->Name = L"tbxA3init2";
				 this->tbxA3init2->Size = System::Drawing::Size(78, 20);
				 this->tbxA3init2->TabIndex = 57;
				 this->tbxA3init2->Text = L"0";
				 // 
				 // tbxA2init2
				 // 
				 this->tbxA2init2->Location = System::Drawing::Point(1328, 753);
				 this->tbxA2init2->Name = L"tbxA2init2";
				 this->tbxA2init2->Size = System::Drawing::Size(78, 20);
				 this->tbxA2init2->TabIndex = 58;
				 this->tbxA2init2->Text = L"0";
				 // 
				 // tbxA1init2
				 // 
				 this->tbxA1init2->Location = System::Drawing::Point(1329, 725);
				 this->tbxA1init2->Name = L"tbxA1init2";
				 this->tbxA1init2->Size = System::Drawing::Size(78, 20);
				 this->tbxA1init2->TabIndex = 59;
				 this->tbxA1init2->Text = L"0";
				 // 
				 // label23
				 // 
				 this->label23->AutoSize = true;
				 this->label23->Location = System::Drawing::Point(1327, 833);
				 this->label23->Name = L"label23";
				 this->label23->Size = System::Drawing::Size(69, 13);
				 this->label23->TabIndex = 55;
				 this->label23->Text = L"initial position";
				 // 
				 // label24
				 // 
				 this->label24->AutoSize = true;
				 this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label24->Location = System::Drawing::Point(39, 40);
				 this->label24->Name = L"label24";
				 this->label24->Size = System::Drawing::Size(29, 24);
				 this->label24->TabIndex = 60;
				 this->label24->Text = L"X:";
				 // 
				 // label25
				 // 
				 this->label25->AutoSize = true;
				 this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label25->Location = System::Drawing::Point(39, 64);
				 this->label25->Name = L"label25";
				 this->label25->Size = System::Drawing::Size(27, 24);
				 this->label25->TabIndex = 61;
				 this->label25->Text = L"Y:";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label2->Location = System::Drawing::Point(3, 101);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(186, 25);
				 this->label2->TabIndex = 62;
				 this->label2->Text = L"Ball Velocity Vector:";
				 // 
				 // label26
				 // 
				 this->label26->AutoSize = true;
				 this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label26->Location = System::Drawing::Point(38, 152);
				 this->label26->Name = L"label26";
				 this->label26->Size = System::Drawing::Size(27, 24);
				 this->label26->TabIndex = 66;
				 this->label26->Text = L"Y:";
				 // 
				 // label27
				 // 
				 this->label27->AutoSize = true;
				 this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label27->Location = System::Drawing::Point(38, 128);
				 this->label27->Name = L"label27";
				 this->label27->Size = System::Drawing::Size(29, 24);
				 this->label27->TabIndex = 65;
				 this->label27->Text = L"X:";
				 // 
				 // label28
				 // 
				 this->label28->AutoSize = true;
				 this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label28->Location = System::Drawing::Point(40, 414);
				 this->label28->Name = L"label28";
				 this->label28->Size = System::Drawing::Size(164, 25);
				 this->label28->TabIndex = 68;
				 this->label28->Text = L"Simulation Mode:";
				 // 
				 // tbxCameraError
				 // 
				 this->tbxCameraError->Location = System::Drawing::Point(104, 583);
				 this->tbxCameraError->Name = L"tbxCameraError";
				 this->tbxCameraError->Size = System::Drawing::Size(100, 20);
				 this->tbxCameraError->TabIndex = 70;
				 this->tbxCameraError->Text = L"50";
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(924, 801);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(42, 13);
				 this->label6->TabIndex = 71;
				 this->label6->Text = L"forward";
				 // 
				 // label16
				 // 
				 this->label16->AutoSize = true;
				 this->label16->Location = System::Drawing::Point(924, 775);
				 this->label16->Name = L"label16";
				 this->label16->Size = System::Drawing::Size(51, 13);
				 this->label16->TabIndex = 72;
				 this->label16->Text = L"midfielder";
				 // 
				 // label17
				 // 
				 this->label17->AutoSize = true;
				 this->label17->Location = System::Drawing::Point(924, 749);
				 this->label17->Name = L"label17";
				 this->label17->Size = System::Drawing::Size(49, 13);
				 this->label17->TabIndex = 73;
				 this->label17->Text = L"defender";
				 // 
				 // label18
				 // 
				 this->label18->AutoSize = true;
				 this->label18->Location = System::Drawing::Point(924, 725);
				 this->label18->Name = L"label18";
				 this->label18->Size = System::Drawing::Size(60, 13);
				 this->label18->TabIndex = 74;
				 this->label18->Text = L"goalkeeper";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label3->Location = System::Drawing::Point(40, 529);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(88, 25);
				 this->label3->TabIndex = 67;
				 this->label3->Text = L"Camera:";
				 // 
				 // panel3
				 // 
				 this->panel3->Controls->Add(this->label1);
				 this->panel3->Controls->Add(this->PosX);
				 this->panel3->Controls->Add(this->PosY);
				 this->panel3->Controls->Add(this->VelX);
				 this->panel3->Controls->Add(this->VelY);
				 this->panel3->Controls->Add(this->label24);
				 this->panel3->Controls->Add(this->label25);
				 this->panel3->Controls->Add(this->label2);
				 this->panel3->Controls->Add(this->label27);
				 this->panel3->Controls->Add(this->label26);
				 this->panel3->Location = System::Drawing::Point(28, 208);
				 this->panel3->Name = L"panel3";
				 this->panel3->Size = System::Drawing::Size(195, 186);
				 this->panel3->TabIndex = 87;
				 // 
				 // label19
				 // 
				 this->label19->AutoSize = true;
				 this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label19->Location = System::Drawing::Point(32, 557);
				 this->label19->Name = L"label19";
				 this->label19->Size = System::Drawing::Size(46, 20);
				 this->label19->TabIndex = 88;
				 this->label19->Text = L"FPS:";
				 // 
				 // label36
				 // 
				 this->label36->AutoSize = true;
				 this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label36->Location = System::Drawing::Point(32, 581);
				 this->label36->Name = L"label36";
				 this->label36->Size = System::Drawing::Size(52, 20);
				 this->label36->TabIndex = 89;
				 this->label36->Text = L"Error:";
				 // 
				 // tbxTimeZoom
				 // 
				 this->tbxTimeZoom->Location = System::Drawing::Point(110, 659);
				 this->tbxTimeZoom->Name = L"tbxTimeZoom";
				 this->tbxTimeZoom->Size = System::Drawing::Size(100, 20);
				 this->tbxTimeZoom->TabIndex = 91;
				 this->tbxTimeZoom->Text = L"15";
				 // 
				 // label37
				 // 
				 this->label37->AutoSize = true;
				 this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label37->Location = System::Drawing::Point(40, 631);
				 this->label37->Name = L"label37";
				 this->label37->Size = System::Drawing::Size(117, 25);
				 this->label37->TabIndex = 92;
				 this->label37->Text = L"Time Zoom:";
				 // 
				 // label29
				 // 
				 this->label29->AutoSize = true;
				 this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label29->Location = System::Drawing::Point(703, 865);
				 this->label29->Name = L"label29";
				 this->label29->Size = System::Drawing::Size(27, 24);
				 this->label29->TabIndex = 102;
				 this->label29->Text = L"Y:";
				 // 
				 // label30
				 // 
				 this->label30->AutoSize = true;
				 this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label30->Location = System::Drawing::Point(703, 841);
				 this->label30->Name = L"label30";
				 this->label30->Size = System::Drawing::Size(29, 24);
				 this->label30->TabIndex = 101;
				 this->label30->Text = L"X:";
				 // 
				 // label31
				 // 
				 this->label31->AutoSize = true;
				 this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label31->Location = System::Drawing::Point(696, 814);
				 this->label31->Name = L"label31";
				 this->label31->Size = System::Drawing::Size(206, 20);
				 this->label31->TabIndex = 100;
				 this->label31->Text = L"Current Ball Velocity Vector:";
				 // 
				 // label32
				 // 
				 this->label32->AutoSize = true;
				 this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label32->Location = System::Drawing::Point(703, 774);
				 this->label32->Name = L"label32";
				 this->label32->Size = System::Drawing::Size(27, 24);
				 this->label32->TabIndex = 99;
				 this->label32->Text = L"Y:";
				 // 
				 // label33
				 // 
				 this->label33->AutoSize = true;
				 this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label33->Location = System::Drawing::Point(703, 750);
				 this->label33->Name = L"label33";
				 this->label33->Size = System::Drawing::Size(29, 24);
				 this->label33->TabIndex = 98;
				 this->label33->Text = L"X:";
				 // 
				 // label34
				 // 
				 this->label34->AutoSize = true;
				 this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label34->Location = System::Drawing::Point(696, 723);
				 this->label34->Name = L"label34";
				 this->label34->Size = System::Drawing::Size(156, 20);
				 this->label34->TabIndex = 97;
				 this->label34->Text = L"Current Ball Position:";
				 // 
				 // ballCurrentVelocityY
				 // 
				 this->ballCurrentVelocityY->Location = System::Drawing::Point(745, 868);
				 this->ballCurrentVelocityY->Name = L"ballCurrentVelocityY";
				 this->ballCurrentVelocityY->Size = System::Drawing::Size(78, 20);
				 this->ballCurrentVelocityY->TabIndex = 96;
				 this->ballCurrentVelocityY->Text = L"0";
				 // 
				 // ballCurrentVelocityX
				 // 
				 this->ballCurrentVelocityX->Location = System::Drawing::Point(747, 842);
				 this->ballCurrentVelocityX->Name = L"ballCurrentVelocityX";
				 this->ballCurrentVelocityX->Size = System::Drawing::Size(76, 20);
				 this->ballCurrentVelocityX->TabIndex = 95;
				 this->ballCurrentVelocityX->Text = L"0";
				 // 
				 // ballCurrentPositionY
				 // 
				 this->ballCurrentPositionY->Location = System::Drawing::Point(747, 777);
				 this->ballCurrentPositionY->Name = L"ballCurrentPositionY";
				 this->ballCurrentPositionY->Size = System::Drawing::Size(76, 20);
				 this->ballCurrentPositionY->TabIndex = 94;
				 this->ballCurrentPositionY->Text = L"0";
				 // 
				 // ballCurrentPositionX
				 // 
				 this->ballCurrentPositionX->Location = System::Drawing::Point(747, 751);
				 this->ballCurrentPositionX->Name = L"ballCurrentPositionX";
				 this->ballCurrentPositionX->Size = System::Drawing::Size(76, 20);
				 this->ballCurrentPositionX->TabIndex = 93;
				 this->ballCurrentPositionX->Text = L"0";
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::SystemColors::Control;
				 this->ClientSize = System::Drawing::Size(1904, 1041);
				 this->Controls->Add(this->label29);
				 this->Controls->Add(this->label30);
				 this->Controls->Add(this->label31);
				 this->Controls->Add(this->label32);
				 this->Controls->Add(this->label33);
				 this->Controls->Add(this->label34);
				 this->Controls->Add(this->ballCurrentVelocityY);
				 this->Controls->Add(this->ballCurrentVelocityX);
				 this->Controls->Add(this->ballCurrentPositionY);
				 this->Controls->Add(this->ballCurrentPositionX);
				 this->Controls->Add(this->label37);
				 this->Controls->Add(this->tbxTimeZoom);
				 this->Controls->Add(this->label36);
				 this->Controls->Add(this->label19);
				 this->Controls->Add(this->panel3);
				 this->Controls->Add(this->label6);
				 this->Controls->Add(this->label16);
				 this->Controls->Add(this->label17);
				 this->Controls->Add(this->label18);
				 this->Controls->Add(this->tbxCameraError);
				 this->Controls->Add(this->label28);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->tbxA4init2);
				 this->Controls->Add(this->tbxA3init2);
				 this->Controls->Add(this->tbxA2init2);
				 this->Controls->Add(this->tbxA1init2);
				 this->Controls->Add(this->label23);
				 this->Controls->Add(this->tbxA4init);
				 this->Controls->Add(this->tbxA3init);
				 this->Controls->Add(this->tbxA2init);
				 this->Controls->Add(this->tbxA1init);
				 this->Controls->Add(this->label22);
				 this->Controls->Add(this->StrategyListBox2);
				 this->Controls->Add(this->StrategyListBox1);
				 this->Controls->Add(this->tbxA4mode2);
				 this->Controls->Add(this->tbxA4desP2);
				 this->Controls->Add(this->tbxA4Y2);
				 this->Controls->Add(this->tbxA3mode2);
				 this->Controls->Add(this->tbxA3desP2);
				 this->Controls->Add(this->tbxA3Y2);
				 this->Controls->Add(this->tbxA2mode2);
				 this->Controls->Add(this->tbxA2desP2);
				 this->Controls->Add(this->tbxA2Y2);
				 this->Controls->Add(this->tbxA1mode2);
				 this->Controls->Add(this->tbxA1desP2);
				 this->Controls->Add(this->tbxA1Y2);
				 this->Controls->Add(this->label13);
				 this->Controls->Add(this->label14);
				 this->Controls->Add(this->label15);
				 this->Controls->Add(this->tbxMode2);
				 this->Controls->Add(this->label20);
				 this->Controls->Add(this->label21);
				 this->Controls->Add(this->tbxA4mode);
				 this->Controls->Add(this->tbxA4desP);
				 this->Controls->Add(this->tbxA4Y);
				 this->Controls->Add(this->tbxA3mode);
				 this->Controls->Add(this->tbxA3desP);
				 this->Controls->Add(this->tbxA3Y);
				 this->Controls->Add(this->tbxA2mode);
				 this->Controls->Add(this->tbxA2desP);
				 this->Controls->Add(this->tbxA2Y);
				 this->Controls->Add(this->tbxA1mode);
				 this->Controls->Add(this->tbxA1desP);
				 this->Controls->Add(this->tbxA1Y);
				 this->Controls->Add(this->label12);
				 this->Controls->Add(this->label11);
				 this->Controls->Add(this->label10);
				 this->Controls->Add(this->label9);
				 this->Controls->Add(this->label8);
				 this->Controls->Add(this->label7);
				 this->Controls->Add(this->goalkeeper);
				 this->Controls->Add(this->tbxMode1);
				 this->Controls->Add(this->label5);
				 this->Controls->Add(this->label4);
				 this->Controls->Add(this->tbxFPS);
				 this->Controls->Add(this->PauseCont);
				 this->Controls->Add(this->panel2);
				 this->Controls->Add(this->panel1);
				 this->Controls->Add(this->buttonStop);
				 this->Controls->Add(this->pictureBox1);
				 this->Controls->Add(this->buttonStart);
				 this->Name = L"Form1";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"Strategy Simulation GUI";
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 this->panel1->ResumeLayout(false);
				 this->panel1->PerformLayout();
				 this->panel2->ResumeLayout(false);
				 this->panel2->PerformLayout();
				 this->panel3->ResumeLayout(false);
				 this->panel3->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion










};
}
