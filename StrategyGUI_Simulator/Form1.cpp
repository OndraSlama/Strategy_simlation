#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace StrategyGUISimulator;

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	StrategyGUISimulator::Form1 form;
	Application::Run(%form);
}

Form1::	~Form1()
{
	if (components)
	{
		delete components;
	}
}

Form1::Form1(void)
{
	InitializeComponent();

	cameraFPS = Int32::Parse(tbxFPS->Text);

	std::srand(std::time(0));

	strategy1 = new StrategyC();
	strategy2 = new StrategyB();
	
	StrategyListBox1->Items->Add("Strategy B");
	StrategyListBox1->Items->Add("Strategy C");

	// default select strategy C
	StrategyListBox1->SelectedIndex = 1;

	StrategyListBox2->Items->Add("Strategy B");
	StrategyListBox2->Items->Add("Strategy C");

	// default select strategy B
	StrategyListBox2->SelectedIndex = 0;

	g = pictureBox1->CreateGraphics();
}

/////


void Form1::buttonStart_Click(Object^  sender, EventArgs^  e)
{
	buttonStop->Enabled = true;
	PauseCont->Enabled = true;
	PauseCont->Text = "Pause";
	
	if (strategy1!=nullptr)
	{
		delete strategy1;
	}
	if (strategy2 != nullptr)
	{
		delete strategy2;
	}

	// init strategy 1
	switch (StrategyListBox1->SelectedIndex)		
	{
	case 0:
		strategy1 = new StrategyB();
		break;

	case 1:
		strategy1 = new StrategyC();
		break;

	default:
		break;
	}

	// init strategy 2
	switch (StrategyListBox2->SelectedIndex)
	{
	case 0:
		strategy2 = new StrategyB();
		break;

	case 1:
		strategy2 = new StrategyC();
		break;

	default:
		break;
	}

	// simulation setup
	sim = new Sim();
	sim->setup();

	// get ball
	int xDiff = Int32::Parse(VelX->Text);
	int yDiff = Int32::Parse(VelY->Text);
	
	sim->ball->position.x = Int32::Parse(PosX->Text);
	sim->ball->position.y = Int32::Parse(PosY->Text);
	sim->ball->velocity = Vec2(xDiff*1000, yDiff*1000);	// ondra ma ve fyzice sekundy, ja milisekundy

	ball = new Ball(sim->ball->radius, Vector(sim->ball->velocity.x/1000, sim->ball->velocity.y/1000), Point(sim->ball->position.x, sim->ball->position.y), 0);
	ball->lastCenter = Point(ball->center.X - xDiff, ball->center.Y - yDiff);



	if (dynamicS->Checked)
	{
		StartDynamicSimulation();
	}
	else
	{
		StartStaticSimulation();
	}



	pictureBox1->Refresh();
	UpdateGUI();
}


/////////////////////////

void Form1::buttonStop_Click(Object^  sender, EventArgs^  e)
{
	PauseCont->Enabled = false;

	timerMain->Stop();

	// delete sim
	if (sim!=nullptr)
	{
		sim->del();
		delete sim;
	}

	
		buttonStop->Enabled = false;

}
///////////////////////



void Form1::pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	// draw goals
	e->Graphics->DrawRectangle(System::Drawing::Pens::Black, 0, 0, 1209, 702);

	System::Drawing::Pen^ blackPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 3.0f);
	e->Graphics->DrawLine(blackPen, 2, 244, 2, 459);
	e->Graphics->DrawLine(blackPen, 1207, 244, 1207, 459);


	// draw side sector lines
	array<Drawing::Point>^ pointsUpper = { Drawing::Point(10, 0), Drawing::Point(170, 45), Drawing::Point(1040, 45), Drawing::Point(1200, 0) };
	e->Graphics->DrawLines(System::Drawing::Pens::Black, pointsUpper);


	array<Drawing::Point>^ pointsLower = { Drawing::Point(10, 703), Drawing::Point(170, 658), Drawing::Point(1040, 658), Drawing::Point(1200, 703) };
	e->Graphics->DrawLines(System::Drawing::Pens::Black, pointsLower);

	e->Graphics->DrawLine(System::Drawing::Pens::Black, 0, 253, 170, 45);
	e->Graphics->DrawLine(System::Drawing::Pens::Black, 1210, 253, 1040, 45);

	e->Graphics->DrawLine(System::Drawing::Pens::Black, 0, 450, 170, 658);
	e->Graphics->DrawLine(System::Drawing::Pens::Black, 1210, 450, 1040, 658);


	// draw ball
	int ballDrawX = (ball->center.X - ball->radius) / 10;
	int ballDrawy = (ball->center.Y / 10 - 351.5)*-1 - ball->radius / 10;
	e->Graphics->FillEllipse(System::Drawing::Brushes::Black, ballDrawX, ballDrawy, 2 * ball->radius / 10, 2 * ball->radius / 10);

#pragma region strategy 1

	//strategy 1
	// draw dummies
	for (auto& axis : strategy1->axes)
	{
		e->Graphics->DrawLine(System::Drawing::Pens::Black, axis.X / 10, 0, axis.X / 10, 703);

		for (auto& dummy : axis.dummies)
		{
			switch (axis.mode)
			{
			case forwardDefense:
				e->Graphics->FillRectangle(System::Drawing::Brushes::Red, System::Drawing::Rectangle((axis.X - DummyX / 2 + axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
				break;

			case backwardDefense:
				e->Graphics->FillRectangle(System::Drawing::Brushes::Red, System::Drawing::Rectangle((axis.X - DummyX / 2 + axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
				break;

			case forwardShoot:
				e->Graphics->FillRectangle(System::Drawing::Brushes::Green, System::Drawing::Rectangle((axis.X - DummyX / 2 + axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
				break;

			case backwardShoot:
				e->Graphics->FillRectangle(System::Drawing::Brushes::Green, System::Drawing::Rectangle((axis.X - DummyX / 2 + axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
				break;

			case raised:
				e->Graphics->FillRectangle(System::Drawing::Brushes::Gray, System::Drawing::Rectangle((axis.X - DummyX / 2 + axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
				break;

			case straight:
				e->Graphics->FillRectangle(System::Drawing::Brushes::Red, System::Drawing::Rectangle((axis.X - DummyX / 2 + axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
				break;
			case exactAngle:
				e->Graphics->FillRectangle(System::Drawing::Brushes::Red, System::Drawing::Rectangle((axis.X - DummyX / 2 + axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
				break;

			default:
				break;
			}
		}
	}

	// draw trajectories
	for (auto const& value : strategy1->trajectory)
	{
		e->Graphics->DrawLine(System::Drawing::Pens::Red, (int)value.X1 / 10, (value.Y1 / 10 - 351.5)*-1, (int)value.X2 / 10, (value.Y2 / 10 - 351.5)*-1);
	}

	// draw intersections

	for (auto& axis : strategy1->axes)
	{
		{
			e->Graphics->FillEllipse(System::Drawing::Brushes::Black, System::Drawing::Rectangle(axis.X / 10 - 6, ((axis.intersectionY / 10 - 351.5)*-1) - 6, 12, 12));
			e->Graphics->FillEllipse(System::Drawing::Brushes::Violet, System::Drawing::Rectangle(axis.X / 10 - 5, ((axis.desiredIntercept / 10 - 351.5)*-1) - 5, 10, 10));

		}
	}
#pragma endregion

#pragma region strategy 2
	//strategy2				 
	// draw dummies
	if (twoTeams->Checked && dynamicS->Checked)
	{
		for (auto& axis : strategy2->axes)
		{
			e->Graphics->DrawLine(System::Drawing::Pens::Black,1210- axis.X / 10, 0,1210- axis.X / 10, 703);

			for (auto& dummy : axis.dummies)
			{
				switch (axis.mode)
				{
				case forwardDefense:
					e->Graphics->FillRectangle(System::Drawing::Brushes::Blue, System::Drawing::Rectangle((12100 - axis.X - DummyX / 2 - axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
					break;

				case backwardDefense:
					e->Graphics->FillRectangle(System::Drawing::Brushes::Blue, System::Drawing::Rectangle((12100 - axis.X - DummyX / 2 - axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
					break;

				case forwardShoot:
					e->Graphics->FillRectangle(System::Drawing::Brushes::BlueViolet, System::Drawing::Rectangle((12100 - axis.X - DummyX / 2 - axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
					break;

				case backwardShoot:
					e->Graphics->FillRectangle(System::Drawing::Brushes::BlueViolet, System::Drawing::Rectangle((12100 - axis.X - DummyX / 2 - axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
					break;

				case raised:
					e->Graphics->FillRectangle(System::Drawing::Brushes::DarkGray, System::Drawing::Rectangle((12100 - axis.X - DummyX / 2 - axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
					break;

				case straight:
					e->Graphics->FillRectangle(System::Drawing::Brushes::Blue, System::Drawing::Rectangle((12100 - axis.X - DummyX / 2 - axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
					break;

				case exactAngle:
					e->Graphics->FillRectangle(System::Drawing::Brushes::Blue, System::Drawing::Rectangle((12100 - axis.X - DummyX / 2 - axis.xDisplacement) / 10, ((dummy.realPos - 3515)*-1 - DummyY / 2) / 10, DummyX / 10, DummyY / 10));
					break;

				default:
					break;
				}
			}
		}
	

		// draw trajectories
		for (auto const& value : strategy2->trajectory)
		{
			e->Graphics->DrawLine(System::Drawing::Pens::Blue, (int)1210 - value.X1 / 10, (int)(value.Y1 / 10 - 351.5)*-1, (int)1210 - value.X2 / 10, (int)(value.Y2 / 10 - 351.5)*-1);
		}

		// draw intersections
		for (auto& axis : strategy2->axes)
		{
			{
				e->Graphics->FillEllipse(System::Drawing::Brushes::Black, System::Drawing::Rectangle(1210 - axis.X / 10 - 6, ((axis.intersectionY / 10 - 351.5)*-1) - 6, 12, 12));
				e->Graphics->FillEllipse(System::Drawing::Brushes::Violet, System::Drawing::Rectangle(1210 - axis.X / 10 - 5, ((axis.desiredIntercept / 10 - 351.5)*-1) - 5, 10, 10));
			}
		}
	}
#pragma endregion

}



///////////////////////

void Form1::MoveAxis()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (player1axes[i]->desiredDisplacement > player1axes[i]->realDisplacement)
		{
			if (player1axes[i]->speed >= 0) // chci nahoru, jedu nahoru
			{
				player1axes[i]->speed += maxAcc;
			}
			else  // else stop
			{
				player1axes[i]->speed = 0;
			}

		}
		else if (player1axes[i]->desiredDisplacement < player1axes[i]->realDisplacement)
		{
			if (player1axes[i]->speed <= 0) // chci dolu, jedu dolu
			{
				player1axes[i]->speed -= maxAcc;
			}
			else  // else stop
			{
				player1axes[i]->speed = 0;
			}
		}

		// reached desired position
		if (abs(player1axes[i]->realDisplacement - player1axes[i]->desiredDisplacement) < abs(player1axes[i]->speed))
		{
			player1axes[i]->realDisplacement = player1axes[i]->desiredDisplacement;
			player1axes[i]->speed = 0;
		}
		else
		{
			player1axes[i]->realDisplacement += player1axes[i]->speed;
		}
	}
	if (twoTeams)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (player2axes[i]->desiredDisplacement > player2axes[i]->realDisplacement)
			{
				if (player2axes[i]->speed >= 0) // chci nahoru, jedu nahoru
				{
					player2axes[i]->speed += maxAcc;
				}
				else  // else stop
				{
					player2axes[i]->speed = 0;
				}

			}
			else if (player2axes[i]->desiredDisplacement < player2axes[i]->realDisplacement)
			{
				if (player2axes[i]->speed <= 0) // chci dolu, jedu dolu
				{
					player2axes[i]->speed -= maxAcc;
				}
				else  // else stop
				{
					player2axes[i]->speed = 0;
				}
			}

			// reached desired position
			if (abs(player2axes[i]->realDisplacement - player2axes[i]->desiredDisplacement) < abs(player2axes[i]->speed))
			{
				player2axes[i]->realDisplacement = player2axes[i]->desiredDisplacement;
				player2axes[i]->speed = 0;
			}
			else
			{
				player2axes[i]->realDisplacement += player2axes[i]->speed;
			}
		}
	}


	for (size_t i = 0; i < 4; i++)
	{
		switch (strategy1->axes[i].mode)
		{
		case forwardShoot:
			if (sim->red[i].angle < 400)
			{
				player1axes[i]->angularSpeed = 40000;
			}
			else
			{
				player1axes[i]->angularSpeed = 0;
				player1axes[i]->mode = forwardDefense;
			}
			break;
		case backwardShoot:
			if (player1axes[i]->angularSpeed == 0)
			{
				sim->red[i].angle = -900;
			}
			if (sim->red[i].angle < 400)
			{
				player1axes[i]->angularSpeed = 40000;
			}
			else
			{
				player1axes[i]->angularSpeed = 0;
				player1axes[i]->mode = forwardDefense;
			}
			break;
		case forwardDefense:
			if (sim->red[i].angle > -120)
			{
				player1axes[i]->angularSpeed = -5000;
			}
			else if (sim->red[i].angle < -150)
			{
				player1axes[i]->angularSpeed = 5000;
			}
			else
			{
				player1axes[i]->angularSpeed = 0;
			}
			break;
		case backwardDefense:
			if (sim->red[i].angle < 200)
			{
				player1axes[i]->angularSpeed = 5000;
			}
			else if (sim->red[i].angle > 220)
			{
				player1axes[i]->angularSpeed = -5000;
			}
			else
			{
				player1axes[i]->angularSpeed = 0;
			}
			break;
		case raised:
			if (sim->red[i].angle > -900)
			{
				player1axes[i]->angularSpeed = -5000;
			}
			else
			{
				player1axes[i]->angularSpeed = 0;
			}
			break;
		case straight:
			if (sim->red[i].angle < -20)
			{
				player1axes[i]->angularSpeed = 5000;
			}
			else if (sim->red[i].angle > 20)
			{
				player1axes[i]->angularSpeed = -5000;
			}
			else
			{
				player1axes[i]->angularSpeed = 0;
			}
			break;
		case exactAngle:
			if (sim->red[i].angle < strategy1->axes->desiredAngle - 20)
			{
				player1axes[i]->angularSpeed = 5000;
			}
			else if (sim->red[i].angle > strategy1->axes->desiredAngle + 20)
			{
				player1axes[i]->angularSpeed = -5000;
			}
			else
			{
				player1axes[i]->angularSpeed = 0;
			}
			break;
		default:
			player1axes[i]->angularSpeed = 0;
			break;
		}

		if (twoTeams)
		{
			switch (strategy2->axes[i].mode)
			{
			case forwardShoot:
				if (sim->blu[i].angle > -400)
				{
					player2axes[i]->angularSpeed = -40000;
				}
				else
				{
					player2axes[i]->angularSpeed = 0;
					player2axes[i]->mode = forwardDefense;
				}
				break;
			case backwardShoot:
				if (player2axes[i]->angularSpeed == 0)
				{
					sim->blu[i].angle = 900;
				}
				if (sim->blu[i].angle > -400)
				{
					player2axes[i]->angularSpeed = -40000;
				}
				else
				{
					player2axes[i]->angularSpeed = 0;
					player2axes[i]->mode = forwardDefense;
				}
				break;
			case forwardDefense:
				if (sim->blu[i].angle < 120)
				{
					player2axes[i]->angularSpeed = 5000;
				}
				else if (sim->blu[i].angle > 150)
				{
					player2axes[i]->angularSpeed = -5000;
				}
				else
				{
					player2axes[i]->angularSpeed = 0;
				}
				break;
			case backwardDefense:
				if (sim->blu[i].angle > -200)
				{
					player2axes[i]->angularSpeed = -5000;
				}
				else if (sim->blu[i].angle < -220)
				{
					player2axes[i]->angularSpeed = 5000;
				}
				else
				{
					player2axes[i]->angularSpeed = 0;
				}
				break;
			case raised:
				if (sim->blu[i].angle < 900)
				{
					player2axes[i]->angularSpeed = 5000;
				}
				else
				{
					player2axes[i]->angularSpeed = 0;
				}
				break;
			case straight:
				if (sim->blu[i].angle < -10)
				{
					player2axes[i]->angularSpeed = 2000;
				} 
				else if (sim->blu[i].angle > 10)
				{
					player2axes[i]->angularSpeed = -2000;
				}
				else
				{
					player2axes[i]->angularSpeed = 0;
				}
				break;
			default:
				player2axes[i]->angularSpeed = 0;
				break;
			}
		}
	}


}



//////////////////////

void Form1::timerMain_Tick(Object^  sender, EventArgs^  e)
{

	if (cyclesToCameraCycle-- == 0)
	{
		timerCamera_Tick();
		cyclesToCameraCycle = cameraInterval;
	}

	// output to framework, desired axis positions
	for (size_t i = 0; i < 4; i++)
	{
		player1axes[i]->desiredDisplacement = strategy1->axes[i].desiredDisplacement;
		player1axes[i]->mode = strategy1->axes[i].mode;


		if (twoTeams)
		{
			player2axes[i]->desiredDisplacement = strategy2->axes[i].desiredDisplacement;
			player2axes[i]->mode = strategy2->axes[i].mode;
		}

	}


	// sim axis velocities input
	for (size_t i = 0; i < 4; i++)
	{
		sim->red[i].velocity.y = player1axes[i]->speed;
		sim->red[i].angular_velocity = player1axes[i]->angularSpeed;

		if (twoTeams)
		{
			sim->blu[i].velocity.y = player2axes[i]->speed;
			sim->blu[i].angular_velocity = player2axes[i]->angularSpeed;
		}
		else
		{
			sim->blu[i].velocity.y = 0;
			sim->blu[i].angular_velocity = 0;

		}

	}

	//motor moves axis

	MoveAxis();

	// sim process
	sim->move();
	sim->collide();




	// read sim axes to strategy and player1axes
	for (size_t i = 0; i < 4; i++)
	{
		player1axes[i]->realDisplacement = sim->red[i].position.y;
		player1axes[i]->xDisplacement = sim->red[i].x_offset;

		if (twoTeams)
		{
			player2axes[i]->realDisplacement = sim->blu[i].position.y;
			player2axes[i]->xDisplacement = sim->blu[i].x_offset;
		}

	}






	//move my ball
	ball->lastCenter = ball->center;
	ball->center = Point(sim->ball->position.x, sim->ball->position.y);

	// goal
	if (ball->center.X-ball->radius>12100)
	{
// TODO goal 
		buttonStop_Click(nullptr, nullptr);
	}
	else if (ball->center.X + ball->radius < 0)
	{
		buttonStop_Click(nullptr, nullptr);
	}
	else 
	{

	// input from framework, axis positions
	for (size_t i = 0; i < 4; i++)
	{
		strategy1->axes[i].realDisplacement = player1axes[i]->realDisplacement;
		strategy1->axes[i].speed = player1axes[i]->speed;
		strategy1->axes[i].xDisplacement = player1axes[i]->xDisplacement;
		strategy1->axes[i].mode = player1axes[i]->mode;


		strategy1->opponentAxes[i].realDisplacement = player2axes[i]->realDisplacement;
		strategy1->opponentAxes[i].speed = player2axes[i]->speed;
		strategy1->opponentAxes[i].mode = player2axes[i]->mode;
		strategy1->opponentAxes[i].xDisplacement = -player2axes[i]->xDisplacement;


		if (twoTeams)
		{
			strategy2->axes[i].realDisplacement = player2axes[i]->realDisplacement;
			strategy2->axes[i].speed = player2axes[i]->speed;
			strategy2->axes[i].xDisplacement = -player2axes[i]->xDisplacement;
			strategy2->axes[i].mode = player2axes[i]->mode;

			strategy2->opponentAxes[i].realDisplacement = player1axes[i]->realDisplacement;
			strategy2->opponentAxes[i].speed = player1axes[i]->speed;
			strategy2->opponentAxes[i].mode = player1axes[i]->mode;
			strategy2->opponentAxes[i].xDisplacement = player1axes[i]->xDisplacement;

		}

	}


	strategy1->Process();

	if (twoTeams->Checked)
	{
		strategy2->Process();
	}

	// redraw the field
	pictureBox1->Refresh();
	UpdateGUI();
}
}



///////////////////////




void Form1::timerCamera_Tick()
{
	int x = rand() % cameraError - cameraError / 2;
	int y = rand() % cameraError - cameraError / 2;

	strategy1->CameraInput(sim->ball->position.x+x, sim->ball->position.y+y);

	if (twoTeams->Checked)
	{
		strategy2->CameraInput(12100 - sim->ball->position.x, sim->ball->position.y);
	}

}


///////////////////////


void Form1::SetupAxis()
{
	player1axes[0] = new Axis({ 0 }, 800, -920, 805);
	player1axes[1] = new Axis({ -1190, 1190 }, 2300, -970, 1070);
	player1axes[2] = new Axis({ -2380,-1190,0,1190,2380 }, 5300, -540, 560);
	player1axes[3] = new Axis({ -2080,0,2080 }, 8300, -800, 870);

	player2axes[0] = new Axis({ 0 }, 800, -920, 805);
	player2axes[1] = new Axis({ -1190, 1190 }, 2300, -970, 1070);
	player2axes[2] = new Axis({ -2380,-1190,0,1190,2380 }, 5300, -540, 560);
	player2axes[3] = new Axis({ -2080,0,2080 }, 8300, -800, 870);
}




///////////////////////



void Form1::SimType_CheckedChanged(Object^  sender, EventArgs^  e)
{
	dynamicS->Checked != dynamicS->Checked;
	staticS->Checked != staticS->Checked;
}



void Form1::TeamCount_CheckedChanged(Object^  sender, EventArgs^  e)
{
	oneTeam->Checked != oneTeam->Checked;
	twoTeams->Checked != twoTeams->Checked;
}

void Form1::PauseCont_Click(Object^  sender, EventArgs^  e)
{
	if (dynamicS->Checked)
	{
		if (timerMain->Enabled)
		{
			((Button^)sender)->Text = "Continue";
			timerMain->Stop();
		}
		else
		{
			((Button^)sender)->Text = "Pause";
			timerMain->Start();
		}
	}
}

void Form1::UpdateGUI()
{

	// ball
	ballCurrentPositionX->Text = ((int)sim->ball->position.x).ToString();
	ballCurrentPositionY->Text = ((int)sim->ball->position.y).ToString();

	ballCurrentVelocityX->Text = ((int)sim->ball->velocity.x/1000).ToString();
	ballCurrentVelocityY->Text = ((int)sim->ball->velocity.y/1000).ToString();


	// strategy 1
	
	// strategy mode
	tbxMode1->Text = StrategyModeEnumToString(strategy1->mode);

	// desired axis position
	tbxA1desP->Text = strategy1->axes[0].desiredDisplacement.ToString();
	tbxA2desP->Text = strategy1->axes[1].desiredDisplacement.ToString();
	tbxA3desP->Text = strategy1->axes[2].desiredDisplacement.ToString();
	tbxA4desP->Text = strategy1->axes[3].desiredDisplacement.ToString();


	// axis modes
	tbxA1mode->Text = AxisModeEnumToString(strategy1->axes[0].mode);
	tbxA2mode->Text = AxisModeEnumToString(strategy1->axes[1].mode);
	tbxA3mode->Text = AxisModeEnumToString(strategy1->axes[2].mode);
	tbxA4mode->Text = AxisModeEnumToString(strategy1->axes[3].mode);

	// axis Y
	tbxA1Y->Text = strategy1->axes[0].realDisplacement.ToString();
	tbxA2Y->Text = strategy1->axes[1].realDisplacement.ToString();
	tbxA3Y->Text = strategy1->axes[2].realDisplacement.ToString();
	tbxA4Y->Text = strategy1->axes[3].realDisplacement.ToString();


	// strategy 2
	if (twoTeams->Checked)
	{
		// strategy mode
		tbxMode2->Text = StrategyModeEnumToString(strategy2->mode);

		// desired axis position
		tbxA1desP2->Text = strategy2->axes[0].desiredDisplacement.ToString();
		tbxA2desP2->Text = strategy2->axes[1].desiredDisplacement.ToString();
		tbxA3desP2->Text = strategy2->axes[2].desiredDisplacement.ToString();
		tbxA4desP2->Text = strategy2->axes[3].desiredDisplacement.ToString();


		// axis modes
		tbxA1mode2->Text = AxisModeEnumToString(strategy2->axes[0].mode);
		tbxA2mode2->Text = AxisModeEnumToString(strategy2->axes[1].mode);
		tbxA3mode2->Text = AxisModeEnumToString(strategy2->axes[2].mode);
		tbxA4mode2->Text = AxisModeEnumToString(strategy2->axes[3].mode);

		// axis Y
		tbxA1Y2->Text = strategy2->axes[0].realDisplacement.ToString();
		tbxA2Y2->Text = strategy2->axes[1].realDisplacement.ToString();
		tbxA3Y2->Text = strategy2->axes[2].realDisplacement.ToString();
		tbxA4Y2->Text = strategy2->axes[3].realDisplacement.ToString();
	}

	if (staticS)
	{
		tbxA1Y->Text = strategy1->axes[0].desiredDisplacement.ToString();
		tbxA2Y->Text = strategy1->axes[1].desiredDisplacement.ToString();
		tbxA3Y->Text = strategy1->axes[2].desiredDisplacement.ToString();
		tbxA4Y->Text = strategy1->axes[3].desiredDisplacement.ToString();

		// strategy mode
		tbxMode2->Text ="";

		// desired axis position
		tbxA1desP2->Text = "";
		tbxA2desP2->Text = "";
		tbxA3desP2->Text = "";
		tbxA4desP2->Text = "";


		// axis modes
		tbxA1mode2->Text = "";
		tbxA2mode2->Text = "";
		tbxA3mode2->Text = "";
		tbxA4mode2->Text = "";

		// axis Y
		tbxA1Y2->Text = "";
		tbxA2Y2->Text = "";
		tbxA3Y2->Text = "";
		tbxA4Y2->Text = "";
	}
}

String^ Form1::StrategyModeEnumToString(int i)
{
	switch (i)
	{
	case defense:
		return "defense";

	case attack:
		return "attack";

	default:
		return "";
		break;
	}
}

String^ Form1::AxisModeEnumToString(int i)
{
	switch (i)
	{
	case forwardDefense:
		return "forward defense";

	case backwardDefense:
		return "backward defense";

	case forwardShoot:
		return "forward shoot";

	case backwardShoot:
		return "backward shoot";

	case raised:
		return "raised";

	case straight:
		return "straight";

	default:
		return "";
		break;
	}
}

void Form1::StartStaticSimulation()
{
	
	strategy1->axes[0].realDisplacement = Int32::Parse(tbxA1init->Text);
	strategy1->opponentAxes[0].realDisplacement= Int32::Parse(tbxA1init->Text);
	strategy1->axes[1].realDisplacement = Int32::Parse(tbxA2init->Text);
	strategy1->opponentAxes[1].realDisplacement = Int32::Parse(tbxA2init->Text);
	strategy1->axes[2].realDisplacement = Int32::Parse(tbxA3init->Text);
	strategy1->opponentAxes[2].realDisplacement = Int32::Parse(tbxA3init->Text);
	strategy1->axes[3].realDisplacement = Int32::Parse(tbxA4init->Text);
	strategy1->opponentAxes[3].realDisplacement = Int32::Parse(tbxA4init->Text);




	strategy2->axes[0].realDisplacement = Int32::Parse(tbxA1init2->Text);
	strategy2->axes[1].realDisplacement = Int32::Parse(tbxA2init2->Text);
	strategy2->axes[2].realDisplacement = Int32::Parse(tbxA3init2->Text);
	strategy2->axes[3].realDisplacement = Int32::Parse(tbxA4init2->Text);


	strategy1->ball = Ball();
	strategy1->ball.center = ball->center;
	strategy1->ball.lastCenter = ball->lastCenter;
	strategy1->ball.vector = ball->vector;
	
	strategy1->ball.vector.length = sqrt(ball->vector.X *ball->vector.X + ball->vector.Y * ball->vector.Y);
	strategy1->ball.vector.X = strategy1->ball.vector.X / strategy1->ball.vector.length;
	strategy1->ball.vector.Y = strategy1->ball.vector.Y / strategy1->ball.vector.length;
	strategy1->ball.speed = 10;

	strategy1->CalculateTrajectory(); // jen po X krajni
	strategy1->CalculateAxesIntersections();


	strategy1->Process();

	for (int i = 0;  i < 4; i++)
	{
		for (int j = 0; j < strategy1->axes[i].dummies.size(); j++)
		{
			strategy1->axes[i].dummies[j].realPos = strategy1->axes[i].desiredDisplacement + strategy1->axes[i].dummies[j].offset;
		}
	}



}

void Form1::StartDynamicSimulation()
{

	TimeZoom = Int32::Parse(tbxTimeZoom->Text);
	timerMain->Interval = TimeZoom >= 10 ? TimeZoom : 10;
	cameraFPS = Int32::Parse(tbxFPS->Text);
	cameraInterval = 1000 / cameraFPS;
	
	cameraError= abs(Int32::Parse(tbxCameraError->Text));

	// v PLC bezi v 2ms tasku
	cyclesToCameraCycle = cameraInterval / 2;



	g->Clear(pictureBox1->BackColor);
	pictureBox1->Refresh();

	SetupAxis();








	// process strategy1
	strategy1->Process();
	if (twoTeams->Checked)
	{
		strategy2->Process();
	}
	else
	{
		sim->blu[0].angle = 900;
		sim->blu[1].angle = 900;
		sim->blu[2].angle = 900;
		sim->blu[3].angle = 900;
	}

		timerMain->Start();
	
}


