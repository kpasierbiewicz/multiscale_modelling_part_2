//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <vcl.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int **table;
int sizeTable = 302;
bool tableExist = false;

int *x = new int[sizeTable];
int *y = new int[sizeTable];

int amount = 2;
int steps = 5;
double jgb = 1;
int stop = 0;
int beforeEnergy = 0;
int afterEnergy = 0;

int **energyTable;
int energyInside = 0;
int energyOnEdge = 0;
bool energySwitch = false;

int energyHomogenous = 0;
int energyHeterogenous = 0;
int power = 0;
int optionEnergyDistribution = 0;
int nucleonType = 0;
int nucleonDystribution = 0;
int amountRecrystalizationNucleons = 0;
int stepsRecrystalization = 0;
int change = 0;
int **energyRecrystalizationTable;

int **neighborhoodTable;

void createTable()
{
        table = new int*[sizeTable];
        energyTable = new int*[sizeTable];
        energyRecrystalizationTable = new int*[sizeTable];
        neighborhoodTable = new int*[sizeTable];

        for (int i = 0; i < sizeTable; i++)
        {
                table[i] = new int[sizeTable];
                energyTable[i] = new int[sizeTable];
                energyRecrystalizationTable[i] = new int[sizeTable];
                neighborhoodTable[i] = new int[sizeTable];
        }

        for (int i = 0; i < sizeTable; i++)
        {
                for (int j = 0; j < sizeTable; j++)
                {
                        table[i][j] = 0;
                        energyTable[i][j] = 0;
                        energyRecrystalizationTable[i][j] = 0;
                        neighborhoodTable[i][j] = 0;
                }
        }

        tableExist = true;
}

void deleteTable()
{
    if (tableExist == true)
    {
        for (int i = 0; i < sizeTable; i++)
        {
                delete [] table[i];
                delete [] energyTable[i];
                delete [] energyRecrystalizationTable[i];
                delete [] neighborhoodTable[i];
        }
                delete [] table;
                delete [] energyTable;
                delete [] energyRecrystalizationTable;
                delete [] neighborhoodTable;
                delete [] x;
                delete [] y;
    }
    tableExist = false;
}

void generateMicrostructure()
{
  for(int i=0; i<= sizeTable - 1; i++)
        for(int j=0; j<=sizeTable - 1; j++)
                if (table[i][j] != 200)
                {
                        table[i][j] = ((rand() % (amount + 1)) +  1);
                }
}

void generateMicrostructureCA()
{
        for (int i = 0; i < amount; i++)
        {
                int x = (rand() % (sizeTable - 2)) + 1;
                int y = (rand() % (sizeTable - 2)) + 1;
                if (table[x][y] != 200)
                {
                        table[x][y] = ((rand() % (amount + 1)) +  1);
                }
        }
}

void startSimulationMonteCarlo()
{
        int beforeID = 0;
        for (int i = 0; i <= sizeTable - 1; i++)
        {
                beforeEnergy = 0;
                afterEnergy = 0;
                x[i] = (rand() % (sizeTable - 2)) + 1;
                y[i] = (rand() % (sizeTable - 2)) + 1;


                if ((table[(x[i])][(y[i])]) != (table[(x[i] - 1)][(y[i])])) beforeEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i] - 1)][(y[i] - 1)])) beforeEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i] - 1)][(y[i] + 1)])) beforeEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i]) - 1]))  beforeEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i] +1 )]))  beforeEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i] + 1)][(y[i] -1 )]))  beforeEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i] +1 )][(y[i])])) beforeEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i] + 1)][(y[i] + 1)])) beforeEnergy++;

                beforeID = table[(x[i])][(y[i])];
                table[x[i]][y[i]] = rand ()% (amount + 1) + 1;

                if ((table[(x[i])][(y[i])]) != (table[(x[i]-1)][(y[i])])) afterEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i]-1)][(y[i]-1)])) afterEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i]-1)][(y[i]+1)])) afterEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i])-1]))  afterEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i]+1)]))  afterEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i]+1)][(y[i]-1)]))  afterEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i]+1)][(y[i])])) afterEnergy++;
                if ((table[(x[i])][(y[i])]) != (table[(x[i]+1)][(y[i]+1)])) afterEnergy++;

                if (afterEnergy * jgb - beforeEnergy * jgb > 0)
                        table[(x[i])][(y[i])] = beforeID;
        }
}

void homogeusEnergyDistribution()
{
        for (int i = 0; i < sizeTable; i++)
        {
                for (int j = 0; j < sizeTable; j++)
                {
                        if (table[i][j] != 0)
                                energyTable[i][j] = energyInside;
                }
        }
}

void heterogenousEnergyDistribution()
{
      for (int i = 0; i < sizeTable - 2; i++)
      {
                for (int j = 0; j < sizeTable - 2; j++)
                {       if (table[i][j] != 0)
                        {
                                if (table[i][j] != table[i][j + 1])
                                        energyTable[i][j] = energyOnEdge;
                                else if (table[i][j] == table[i][j + 1])
                                        energyTable[i][j] = energyInside;

                                if (table[i][j] != table[i + 1][j])
                                        energyTable[i][j] = energyOnEdge;
                                else if (table[i][j] == table[i + 1][j])
                                        energyTable[i][j] = energyInside;

                                if (table[i][j] != table[i + 1][j + 1])
                                        energyTable[i][j] = energyOnEdge;
                                else if (table[i][j] != table[i + 1][j + 1])
                                        energyTable[i][j] = energyInside;
                        }
                }
      }

      for (int i = sizeTable - 1; i > 0; i--)
      {
                for (int j = sizeTable - 1; j > 0; j--)
                {
                        if (table[i][j] != table[i][j - 1])
                                energyTable[i][j] = energyOnEdge;
                        else if (table[i][j] == table[i][j - 1])
                                energyTable[i][j] = energyInside;

                        if (table[i][j] != table[i - 1][j])
                                energyTable[i][j] = energyOnEdge;
                        else if (table[i][j] != table[i - 1][j])
                                energyTable[i][j] = energyInside;

                        if (table[i][j] != table[i - 1][j - 1])
                                energyTable[i][j] = energyOnEdge;
                        else if (table[i][j] != table[i - 1][j - 1])
                                energyTable[i][j] = energyInside;
                }
      }
}

void addEenergyRecrystalization()
{       if (optionEnergyDistribution == 1)
        {
                for (int i = 0; i < sizeTable; i++)
                        for (int j = 0; j < sizeTable; j++)
                                if (table[i][j] != 0)
                                        energyRecrystalizationTable[i][j] = energyHomogenous;
        }

        if (optionEnergyDistribution == 0)
        {
               for (int i = 0; i < sizeTable - 2; i++)
                        for (int j = 0; j < sizeTable - 2; j++)
                                if ((table[i][j] != table[i + 1][j]) || (table[i][j] != table[i][j+1]) && table[i][j] != 0)
                                        energyRecrystalizationTable[i][j] = energyHeterogenous;
        }

        for (int i = 0; i < sizeTable; i++)
                for (int j = 0; j < sizeTable; j++)
                        if (table[i][j] > 100)
                              energyRecrystalizationTable[i][j] = 0;
}

void addNucleons()
{
                for (int i = 0; i < amountRecrystalizationNucleons; i++)
                {
                        x[i] = rand() % 50 + 1;
                        y[i] = rand() % 50 + 1;
                }

                for (int i = 0; i < amountRecrystalizationNucleons; i++)
                {
                        table[(x[i])][(y[i])] = 0;
                        energyTable[(x[i])][(y[i])] = 0;
                }
}

void startRecrystallization()
{
        srand(time(NULL));
        int wholeEnergyBefore = 0;
        int beforeID = 0;
        int counter = 0;
        
        for (int i = 1; i <= sizeTable - 1; i++)
        {
                x[i] = (rand() % (sizeTable - 2)) + 1;
                y[i] = (rand() % (sizeTable - 2)) + 1;

                if (((table[(x[i] - 1)][(y[i])]) > 100) || ((table[(x[i] - 1)][(y[i] - 1)])) ||
                ((table[(x[i] - 1)][(y[i] + 1)])) || ((table[(x[i])][(y[i]) - 1])) ||
                ((table[(x[i])][(y[i] + 1)])) || ((table[(x[i] + 1)][(y[i] - 1)])) ||
                ((table[(x[i] + 1)][(y[i])])) || ((table[(x[i] + 1)][(y[i] + 1)])))
                {
                        if ((table[(x[i])][(y[i])]) != (table[(x[i] - 1)][(y[i])]))
                        {
                                beforeEnergy++;
                                if (table[(x[i] - 1)][(y[i])] > 100) counter++;
                        }

                        if ((table[(x[i])][(y[i])]) != (table[(x[i] - 1)][(y[i] - 1)]))
                        {
                                beforeEnergy++;
                                if (table[(x[i] - 1)][(y[i] - 1)] > 100) counter++;
                        }

                        if ((table[(x[i])][(y[i])]) != (table[(x[i] - 1)][(y[i] + 1)]))
                        {
                                beforeEnergy++;
                                if (table[(x[i] - 1)][(y[i] + 1)] > 100) counter++;
                        }

                        if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i]) - 1]))
                        {
                                beforeEnergy++;
                                if (table[(x[i])][(y[i]) - 1] > 100) counter++;
                        }

                        if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i] +1 )]))
                        {
                                beforeEnergy++;
                                if (table[(x[i])][(y[i] +1 )] > 100) counter++;
                        }

                        if ((table[(x[i])][(y[i])]) != (table[(x[i] + 1)][(y[i] -1 )]))
                        {
                                beforeEnergy++;
                                if (table[(x[i] + 1)][(y[i] -1 )] > 100) counter++;
                        }

                        if ((table[(x[i])][(y[i])]) != (table[(x[i] +1 )][(y[i])]))
                        {
                                beforeEnergy++;
                                if (table[(x[i] +1 )][(y[i])] > 100) counter++;
                        }

                        if ((table[(x[i])][(y[i])]) != (table[(x[i] + 1)][(y[i] + 1)]))
                        {
                                beforeEnergy++;
                                if (table[(x[i] + 1)][(y[i] + 1)] > 100) counter++;
                        }

                        wholeEnergyBefore = beforeEnergy + energyRecrystalizationTable[(x[i])][(y[i])];
                        beforeID = table[(x[i])][(y[i])];

                        if (counter > 0)
                        {
                                table[(x[i])][(y[i])] = rand() % counter;

                                if (table[(x[i]-1)][(y[i])] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i]-1)][(y[i])];
                                }

                                if (table[(x[i]-1)][(y[i]-1)] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i]-1)][(y[i]-1)];
                                }

                                if (table[(x[i]-1)][(y[i]+1)] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i]-1)][(y[i]+1)];
                                }

                                if (table[(x[i])][(y[i])-1] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i])][(y[i]-1)];
                                }

                                if (table[(x[i])][(y[i]+1)] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i])][(y[i]+1)];
                                }

                                if (table[(x[i]+1)][(y[i]-1)] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i]+1)][(y[i]-1)];
                                }

                                if (table[(x[i]+1)][(y[i])] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i]+1)][(y[i])];
                                }

                                if (table[(x[i]+1)][(y[i]+1)] > 100)
                                {
                                        if (table[(x[i])][(y[i])] == 0)
                                                table[(x[i])][(y[i])] = table[(x[i]+1)][(y[i]+1)];
                                }

                                if ((table[(x[i])][(y[i])]) != (table[(x[i]-1)][(y[i])])) afterEnergy++;
                                if ((table[(x[i])][(y[i])]) != (table[(x[i]-1)][(y[i]-1)])) afterEnergy++;
                                if ((table[(x[i])][(y[i])]) != (table[(x[i]-1)][(y[i]+1)])) afterEnergy++;
                                if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i])-1]))  afterEnergy++;
                                if ((table[(x[i])][(y[i])]) != (table[(x[i])][(y[i]+1)]))  afterEnergy++;
                                if ((table[(x[i])][(y[i])]) != (table[(x[i]+1)][(y[i]-1)]))  afterEnergy++;
                                if ((table[(x[i])][(y[i])]) != (table[(x[i]+1)][(y[i])])) afterEnergy++;
                                if ((table[(x[i])][(y[i])]) != (table[(x[i]+1)][(y[i]+1)])) afterEnergy++;

                                if (afterEnergy - wholeEnergyBefore > 0)
                                        table[(x[i])][(y[i])] = beforeID;
                        }
                }
        }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Canvas->Brush->Color = clWhite;
        Canvas->FillRect(Rect(5,5,510,510));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::startSimulationButtonClick(TObject *Sender)
{
        srand(time(NULL));
        energySwitch = false;
        Timer->Enabled=false;
        if (tableExist == false) createTable();

        amount = amountNucleonsComboBox->ItemIndex;
        amount++;
        steps =  timeEdit->Text.ToInt();
        jgb = jgbEdit->Text.ToDouble();
        stop=0;

        if ((amount > 0) && (steps > 0))
                Timer->Enabled=true;


}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerTimer(TObject *Sender)
{
        if (table[1][1] == 0)
        if (stop==0) generateMicrostructure();

        startSimulationMonteCarlo();

        for(int i = 1; i <= 50; i++)
        {
                for(int j = 1; j <= 50; j++)
                {
                        if (table[i][j] == 0) Canvas->Brush->Color = clWhite;
                        else if (table[i][j] == 1) Canvas->Brush->Color = cl3DDkShadow;
                        else if (table[i][j] == 2) Canvas->Brush->Color = clMaroon;
                        else if (table[i][j] == 3) Canvas->Brush->Color = clGreen;
                        else if (table[i][j] == 4) Canvas->Brush->Color = clPurple;
                        else if (table[i][j] == 5)Canvas->Brush->Color = clGray;
                        else if (table[i][j] == 6)Canvas->Brush->Color = clYellow;
                        else if (table[i][j] == 7)Canvas->Brush->Color = clTeal;
                        else if (table[i][j] == 8)Canvas->Brush->Color = clRed;
                        else if (table[i][j] == 9)Canvas->Brush->Color = clLime;
                        else if (table[i][j] == 10)Canvas->Brush->Color = clFuchsia;
                        else if (table[i][j] == 11)Canvas->Brush->Color = clAqua;
                        else if (table[i][j] == 12)Canvas->Brush->Color = clCream;
                        else if (table[i][j] == 13)Canvas->Brush->Color = clMedGray;
                        else if (table[i][j] == 14)Canvas->Brush->Color = clNavy;
                        else if (table[i][j] == 15)Canvas->Brush->Color = clSilver;
                        else if (table[i][j] == 16)Canvas->Brush->Color = clSkyBlue;
                        else if (table[i][j] == 17)Canvas->Brush->Color = clMenu;
                        else if (table[i][j] == 18)Canvas->Brush->Color = clLtGray;
                        else if (table[i][j] == 19)Canvas->Brush->Color = cl3DLight;
                        else if (table[i][j] == 20)Canvas->Brush->Color = clMoneyGreen;
                        else if (table[i][j] == 99)Canvas->Brush->Color = clBlack;
                        else if (table[i][j] == 200) Canvas->Brush->Color = 0xf442f1;
                        else Canvas->Brush->Color = clWhite;

                        Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                }
        }

        if (stop >= steps) Timer->Enabled=false;
        stop=stop+1;
}

void __fastcall TForm1::clearAllButtonClick(TObject *Sender)
{
        deleteTable();
        Canvas->Brush->Color = clWhite;
        Canvas->FillRect(Rect(1,1,510,510));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::showEnergyButtonClick(TObject *Sender)
{
        if (tableExist == true && table[0][0] != 0)
        {
                energyInside = energyInsideEdit->Text.ToInt();
                energyOnEdge = energyOnEdgeEdit->Text.ToInt();

                if (energyDistributionComboBox->Items->Strings[energyDistributionComboBox->ItemIndex] == "Homogenous")
                {
                    homogeusEnergyDistribution();
                }

                if (energyDistributionComboBox->Items->Strings[energyDistributionComboBox->ItemIndex] == "Heterogenous")
                {     if (energyOnEdge > energyInside)
                                heterogenousEnergyDistribution();
                      else
                          for (int i = 0; i < sizeTable; i++)
                                for (int j = 0; j < sizeTable; j++)
                                        energyTable[i][j] = 0;
                }

                for (int i = 1; i <= 50; i++)
                {
                        for (int j = 1; j <= 50; j++)
                        {
                                if (energyTable[i][j] == energyInside)
                                        Canvas->Brush->Color = clBlue;

                               if (energyTable[i][j] == energyOnEdge)
                                     Canvas->Brush->Color = clLime;

                                   Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                        }
                }
        }
        energySwitch = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::startRecrystallizationButtonClick(TObject *Sender)
{
        power = 1;

        amountRecrystalizationNucleons = nucleonRateEdit->Text.ToInt();
        change = 1;

        stepsRecrystalization = recrystallizationStepsEdit->Text.ToInt();

        Timer->Enabled = false;
        Timer2->Enabled = false;
        Timer3->Enabled = false;

        stop = 0;
        Timer3->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
        addNucleons();
        if (energySwitch == false)
        {
                for(int i = 1; i <= 50; i++)
                {
                        for(int j = 1; j <= 50; j++)
                        {
                                if (table[i][j] == 0) Canvas->Brush->Color = clWhite;
                                else if (table[i][j] == 1) Canvas->Brush->Color = cl3DDkShadow;
                                else if (table[i][j] == 2) Canvas->Brush->Color = clMaroon;
                                else if (table[i][j] == 3) Canvas->Brush->Color = clGreen;
                                else if (table[i][j] == 4) Canvas->Brush->Color = clPurple;
                                else if (table[i][j] == 5)Canvas->Brush->Color = clGray;
                                else if (table[i][j] == 6)Canvas->Brush->Color = clYellow;
                                else if (table[i][j] == 7)Canvas->Brush->Color = clTeal;
                                else if (table[i][j] == 8)Canvas->Brush->Color = clPurple;
                                else if (table[i][j] == 9)Canvas->Brush->Color = clLime;
                                else if (table[i][j] == 10)Canvas->Brush->Color = clYellow;
                                else if (table[i][j] == 11)Canvas->Brush->Color = clAqua;
                                else if (table[i][j] == 12)Canvas->Brush->Color = clCream;
                                else if (table[i][j] == 13)Canvas->Brush->Color = clFuchsia;
                                else if (table[i][j] == 14)Canvas->Brush->Color = clNavy;
                                else if (table[i][j] == 15)Canvas->Brush->Color = clSilver;
                                else if (table[i][j] == 16)Canvas->Brush->Color = clSkyBlue;
                                else if (table[i][j] == 17)Canvas->Brush->Color = clMenu;
                                else if (table[i][j] == 18)Canvas->Brush->Color = clLtGray;
                                else if (table[i][j] == 19)Canvas->Brush->Color = cl3DLight;
                                else if (table[i][j] == 20)Canvas->Brush->Color = clMoneyGreen;
                                else if (table[i][j]==101) Canvas->Brush->Color = 0x330099;
                                else if (table[i][j]==102) Canvas->Brush->Color = 0x6633FF;
                                else if (table[i][j]==103) Canvas->Brush->Color = 0x3300CC;
                                else if (table[i][j]==104) Canvas->Brush->Color = 0x3300FF;
                                else if (table[i][j]==105) Canvas->Brush->Color = 0x3333CC;
                                else if (table[i][j]==106) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==107) Canvas->Brush->Color = 0x000099;
                                else if (table[i][j]==108) Canvas->Brush->Color = 0x0000CC;
                                else if (table[i][j]==109) Canvas->Brush->Color = 0x333399;
                                else if (table[i][j]==110) Canvas->Brush->Color = 0x3366FF;
                                else if (table[i][j]==111) Canvas->Brush->Color = 0x003366;
                                else if (table[i][j]==112) Canvas->Brush->Color = 0x0000FF;
                                else if (table[i][j]==113) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==114) Canvas->Brush->Color = 0x0066FF;
                                else if (table[i][j]==115) Canvas->Brush->Color = 0x99CCFF;
                                else if (table[i][j]==116) Canvas->Brush->Color = 0x2A2AA6;
                                else if (table[i][j]==117) Canvas->Brush->Color = 0x0024FF;
                                else if (table[i][j]==118) Canvas->Brush->Color = 0x17178C;
                                else if (table[i][j]==119) Canvas->Brush->Color = 0x6666FF;
                                else if (table[i][j]==120) Canvas->Brush->Color = 0x6666CC;
                                else if (table[i][j]==121) Canvas->Brush->Color = 0x330099;
                                else if (table[i][j]==122) Canvas->Brush->Color = 0x6633FF;
                                else if (table[i][j]==123) Canvas->Brush->Color = 0x3300CC;
                                else if (table[i][j]==124) Canvas->Brush->Color = 0x3300FF;
                                else if (table[i][j]==125) Canvas->Brush->Color = 0x3333CC;
                                else if (table[i][j]==126) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==127) Canvas->Brush->Color = 0x000099;
                                else if (table[i][j]==128) Canvas->Brush->Color = 0x0000CC;
                                else if (table[i][j]==129) Canvas->Brush->Color = 0x333399;
                                else if (table[i][j]==130) Canvas->Brush->Color = 0x3366FF;
                                else if (table[i][j]==131) Canvas->Brush->Color = 0x003366;
                                else if (table[i][j]==132) Canvas->Brush->Color = 0x0000FF;
                                else if (table[i][j]==133) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==134) Canvas->Brush->Color = 0x0066FF;
                                else if (table[i][j]==135) Canvas->Brush->Color = 0x99CCFF;
                                else if (table[i][j]==136) Canvas->Brush->Color = 0x2A2AA6;
                                else if (table[i][j]==137) Canvas->Brush->Color = 0x0024FF;
                                else if (table[i][j]==138) Canvas->Brush->Color = 0x17178C;
                                else if (table[i][j]==139) Canvas->Brush->Color = 0x6666FF;
                                else if (table[i][j]==140) Canvas->Brush->Color = 0x6666CC;
                                else if (table[i][j]==99)  Canvas->Brush->Color = clBlack;

                                Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                        }
                }
        }

        if (energySwitch == true)
        {
                for(int i = 1; i <= 50; i++)
                {
                        for(int j = 1; j <= 50; j++)
                        {
                                if (table[i][j] == 0) Canvas->Brush->Color = 0x191919;
                                else if (table[i][j] == 1) Canvas->Brush->Color = 0x2E2E2E;
                                else if (table[i][j] == 2) Canvas->Brush->Color = 0x434343;
                                else if (table[i][j] == 3) Canvas->Brush->Color = 0x535353;
                                else if (table[i][j] == 4) Canvas->Brush->Color = 0x626262;
                                else if (table[i][j] == 5) Canvas->Brush->Color = 0x878787;
                                else if (table[i][j] == 6) Canvas->Brush->Color = 0x9C9C9C;
                                else if (table[i][j] == 7) Canvas->Brush->Color = 0xBBBBBB;
                                else if (table[i][j] == 8)Canvas->Brush->Color = 0xEFEFEF;
                                else if (table[i][j] == 9)Canvas->Brush->Color = clLime;
                                else if (table[i][j] == 10)Canvas->Brush->Color = clYellow;
                                else if (table[i][j] == 11)Canvas->Brush->Color = clAqua;
                                else if (table[i][j] == 12)Canvas->Brush->Color = clCream;
                                else if (table[i][j] == 13)Canvas->Brush->Color = clFuchsia;
                                else if (table[i][j] == 14)Canvas->Brush->Color = clNavy;
                                else if (table[i][j] == 15)Canvas->Brush->Color = clSilver;
                                else if (table[i][j] == 16)Canvas->Brush->Color = clSkyBlue;
                                else if (table[i][j] == 17)Canvas->Brush->Color = clMenu;
                                else if (table[i][j] == 18)Canvas->Brush->Color = clLtGray;
                                else if (table[i][j] == 19)Canvas->Brush->Color = cl3DLight;
                                else if (table[i][j] == 20)Canvas->Brush->Color = clMoneyGreen;
                                else if (table[i][j]==101) Canvas->Brush->Color = 0x330099;
                                else if (table[i][j]==102) Canvas->Brush->Color = 0x6633FF;
                                else if (table[i][j]==103) Canvas->Brush->Color = 0x3300CC;
                                else if (table[i][j]==104) Canvas->Brush->Color = 0x3300FF;
                                else if (table[i][j]==105) Canvas->Brush->Color = 0x3333CC;
                                else if (table[i][j]==106) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==107) Canvas->Brush->Color = 0x000099;
                                else if (table[i][j]==108) Canvas->Brush->Color = 0x0000CC;
                                else if (table[i][j]==109) Canvas->Brush->Color = 0x333399;
                                else if (table[i][j]==110) Canvas->Brush->Color = 0x3366FF;
                                else if (table[i][j]==111) Canvas->Brush->Color = 0x003366;
                                else if (table[i][j]==112) Canvas->Brush->Color = 0x0000FF;
                                else if (table[i][j]==113) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==114) Canvas->Brush->Color = 0x0066FF;
                                else if (table[i][j]==115) Canvas->Brush->Color = 0x99CCFF;
                                else if (table[i][j]==116) Canvas->Brush->Color = 0x2A2AA6;
                                else if (table[i][j]==117) Canvas->Brush->Color = 0x0024FF;
                                else if (table[i][j]==118) Canvas->Brush->Color = 0x17178C;
                                else if (table[i][j]==119) Canvas->Brush->Color = 0x6666FF;
                                else if (table[i][j]==120) Canvas->Brush->Color = 0x6666CC;
                                else if (table[i][j]==121) Canvas->Brush->Color = 0x330099;
                                else if (table[i][j]==122) Canvas->Brush->Color = 0x6633FF;
                                else if (table[i][j]==123) Canvas->Brush->Color = 0x3300CC;
                                else if (table[i][j]==124) Canvas->Brush->Color = 0x3300FF;
                                else if (table[i][j]==125) Canvas->Brush->Color = 0x3333CC;
                                else if (table[i][j]==126) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==127) Canvas->Brush->Color = 0x000099;
                                else if (table[i][j]==128) Canvas->Brush->Color = 0x0000CC;
                                else if (table[i][j]==129) Canvas->Brush->Color = 0x333399;
                                else if (table[i][j]==130) Canvas->Brush->Color = 0x3366FF;
                                else if (table[i][j]==131) Canvas->Brush->Color = 0x003366;
                                else if (table[i][j]==132) Canvas->Brush->Color = 0x0000FF;
                                else if (table[i][j]==133) Canvas->Brush->Color = 0x000066;
                                else if (table[i][j]==134) Canvas->Brush->Color = 0x0066FF;
                                else if (table[i][j]==135) Canvas->Brush->Color = 0x99CCFF;
                                else if (table[i][j]==136) Canvas->Brush->Color = 0x2A2AA6;
                                else if (table[i][j]==137) Canvas->Brush->Color = 0x0024FF;
                                else if (table[i][j]==138) Canvas->Brush->Color = 0x17178C;
                                else if (table[i][j]==139) Canvas->Brush->Color = 0x6666FF;
                                else if (table[i][j]==140) Canvas->Brush->Color = 0x6666CC;
                                else if (table[i][j]==99)  Canvas->Brush->Color = clBlack;
                                
                                Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                        }
                }
        }

        power--;
        if (power == 0) Timer3->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::startStructureButtonClick(TObject *Sender)
{
       if (methodGenerateStructureComboBox->Items->Strings[methodGenerateStructureComboBox->ItemIndex] == "MC")
       {
                amount = amountNucleonsComboBox->ItemIndex;
                amount++;
                steps =  timeEdit->Text.ToInt();
                jgb = jgbEdit->Text.ToDouble();
                stop=0;

                if ((amount > 0) && (steps > 0))
                        Timer->Enabled=true;
       }

       if (methodGenerateStructureComboBox->Items->Strings[methodGenerateStructureComboBox->ItemIndex] == "CA")
       {
                amount = amountNucleonsComboBox->ItemIndex;
                amount++;
                steps =  timeEdit->Text.ToInt();
                for (int i = 0; i < 1000; i++)
                        generateMicrostructureCA();
                
                        for(int i = 1; i <= 50; i++)
                        {
                                for(int j = 1; j <= 50; j++)
                                {
                                        if (table[i][j] == 0) Canvas->Brush->Color = clWhite;
                                        else if (table[i][j] == 1) Canvas->Brush->Color = cl3DDkShadow;
                                        else if (table[i][j] == 2) Canvas->Brush->Color = clMaroon;
                                        else if (table[i][j] == 3) Canvas->Brush->Color = clGreen;
                                        else if (table[i][j] == 4) Canvas->Brush->Color = clPurple;
                                        else if (table[i][j] == 5)Canvas->Brush->Color = clGray;
                                        else if (table[i][j] == 6)Canvas->Brush->Color = clYellow;
                                        else if (table[i][j] == 7)Canvas->Brush->Color = clTeal;
                                        else if (table[i][j] == 8)Canvas->Brush->Color = clRed;
                                        else if (table[i][j] == 9)Canvas->Brush->Color = clLime;
                                        else if (table[i][j] == 10)Canvas->Brush->Color = clFuchsia;
                                        else if (table[i][j] == 11)Canvas->Brush->Color = clAqua;
                                        else if (table[i][j] == 12)Canvas->Brush->Color = clCream;
                                        else if (table[i][j] == 13)Canvas->Brush->Color = clMedGray;
                                        else if (table[i][j] == 14)Canvas->Brush->Color = clNavy;
                                        else if (table[i][j] == 15)Canvas->Brush->Color = clSilver;
                                        else if (table[i][j] == 16)Canvas->Brush->Color = clSkyBlue;
                                        else if (table[i][j] == 17)Canvas->Brush->Color = clMenu;
                                        else if (table[i][j] == 18)Canvas->Brush->Color = clLtGray;
                                        else if (table[i][j] == 19)Canvas->Brush->Color = cl3DLight;
                                        else if (table[i][j] == 20)Canvas->Brush->Color = clMoneyGreen;
                                        else if (table[i][j] == 99)Canvas->Brush->Color = clBlack;
                                        else if (table[i][j] == 200) Canvas->Brush->Color = 0xf442f1;
                                        else Canvas->Brush->Color = clWhite;

                                        Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                        }
                }

                Timer5->Enabled = true;
       }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer5Timer(TObject *Sender)
{
        stop = 0;

                for (int i = 0; i < sizeTable; i++)
                        for (int j =0; j < sizeTable; j++)
                                neighborhoodTable[i][j] = table[i][j];

                for (int amountNucleon = 0;  amountNucleon < sizeTable; amountNucleon++)
                {
                        for (int i = 1; i < sizeTable - 2; i++)
                        {
                                for (int j = 1; j < sizeTable - 2; j++)
                                {

                                        int counter = 0;
                                        if (neighborhoodTable[i - 1][j] == amountNucleon) counter++;
                                        if (neighborhoodTable[i + 1][j] == amountNucleon) counter++;
                                        if (neighborhoodTable[i][j + 1] == amountNucleon) counter++;
                                        if (neighborhoodTable[i][j - 1] == amountNucleon) counter++;

                                        if (counter == 4)
                                                neighborhoodTable[i][j] = amountNucleon;
                                }
                        }
                }

                for (int i = 0; i < sizeTable; i++)
                        for (int j =0; j < sizeTable; j++)
                                if (table[i][j] != 200)
                                        table[i][j] = neighborhoodTable[i][j];

                        for(int i = 1; i <= 50; i++)
                        {
                                for(int j = 1; j <= 50; j++)
                                {
                                        if (table[i][j] == 0) Canvas->Brush->Color = clWhite;
                                        else if (table[i][j] == 1) Canvas->Brush->Color = cl3DDkShadow;
                                        else if (table[i][j] == 2) Canvas->Brush->Color = clMaroon;
                                        else if (table[i][j] == 3) Canvas->Brush->Color = clGreen;
                                        else if (table[i][j] == 4) Canvas->Brush->Color = clPurple;
                                        else if (table[i][j] == 5)Canvas->Brush->Color = clGray;
                                        else if (table[i][j] == 6)Canvas->Brush->Color = clYellow;
                                        else if (table[i][j] == 7)Canvas->Brush->Color = clTeal;
                                        else if (table[i][j] == 8)Canvas->Brush->Color = clRed;
                                        else if (table[i][j] == 9)Canvas->Brush->Color = clLime;
                                        else if (table[i][j] == 10)Canvas->Brush->Color = clFuchsia;
                                        else if (table[i][j] == 11)Canvas->Brush->Color = clAqua;
                                        else if (table[i][j] == 12)Canvas->Brush->Color = clCream;
                                        else if (table[i][j] == 13)Canvas->Brush->Color = clMedGray;
                                        else if (table[i][j] == 14)Canvas->Brush->Color = clNavy;
                                        else if (table[i][j] == 15)Canvas->Brush->Color = clSilver;
                                        else if (table[i][j] == 16)Canvas->Brush->Color = clSkyBlue;
                                        else if (table[i][j] == 17)Canvas->Brush->Color = clMenu;
                                        else if (table[i][j] == 18)Canvas->Brush->Color = clLtGray;
                                        else if (table[i][j] == 19)Canvas->Brush->Color = cl3DLight;
                                        else if (table[i][j] == 20)Canvas->Brush->Color = clMoneyGreen;
                                        else if (table[i][j] == 99)Canvas->Brush->Color = clBlack;
                                        else if (table[i][j] == 200) Canvas->Brush->Color = 0xf442f1;
                                        else Canvas->Brush->Color = clWhite;

                                        Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                        }
                }
                stop++;

        if (stop >= steps) Timer5->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::generateSubstructureButtonClick(TObject *Sender)
{
      Timer4->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
        srand(time(NULL));
        if (substructureTypeComboBox->Items->Strings[substructureTypeComboBox->ItemIndex] == "Substructure")
        {
                int id = rand() % amount +  1;
                int tmpId = id;
                amount = howManyEdit->Text.ToInt() + 1;
                for (int amountNucleon = 0; amountNucleon < amount; amountNucleon++)
                {
                        for (int i = 0; i < sizeTable; i++)
                        {
                                for (int j = 0; j < sizeTable; j++)
                                {
                                        if (table[i][j] == id)
                                        {
                                                table[i][j] = 200;
                                        }
                                }
                        }

                        do
                        {
                                id = rand() % amount + 1;
                        } while (id == tmpId);
                }

                        Timer4->Enabled = false;
        }

        if (substructureTypeComboBox->Items->Strings[substructureTypeComboBox->ItemIndex] == "Dual phase")
        {
                int id = rand() % amount +  1;
                for (int i = 0; i < sizeTable; i++)
                {
                        for (int j = 0; j < sizeTable; j++)
                        {
                                if (table[i][j] == id)
                                {
                                        table[i][j] = 200;
                                }
                        }
                }
               Timer4->Enabled = false;
        }

        for(int i = 1; i <= 50; i++)
        {
                for(int j = 1; j <= 50; j++)
                {
                        if (table[i][j] == 0) Canvas->Brush->Color = clWhite;
                                        else if (table[i][j] == 1) Canvas->Brush->Color = cl3DDkShadow;
                                        else if (table[i][j] == 2) Canvas->Brush->Color = clMaroon;
                                        else if (table[i][j] == 3) Canvas->Brush->Color = clGreen;
                                        else if (table[i][j] == 4) Canvas->Brush->Color = clPurple;
                                        else if (table[i][j] == 5)Canvas->Brush->Color = clGray;
                                        else if (table[i][j] == 6)Canvas->Brush->Color = clYellow;
                                        else if (table[i][j] == 7)Canvas->Brush->Color = clTeal;
                                        else if (table[i][j] == 8)Canvas->Brush->Color = clRed;
                                        else if (table[i][j] == 9)Canvas->Brush->Color = clLime;
                                        else if (table[i][j] == 10)Canvas->Brush->Color = clFuchsia;
                                        else if (table[i][j] == 11)Canvas->Brush->Color = clAqua;
                                        else if (table[i][j] == 12)Canvas->Brush->Color = clCream;
                                        else if (table[i][j] == 13)Canvas->Brush->Color = clMedGray;
                                        else if (table[i][j] == 14)Canvas->Brush->Color = clNavy;
                                        else if (table[i][j] == 15)Canvas->Brush->Color = clSilver;
                                        else if (table[i][j] == 16)Canvas->Brush->Color = clSkyBlue;
                                        else if (table[i][j] == 17)Canvas->Brush->Color = clMenu;
                                        else if (table[i][j] == 18)Canvas->Brush->Color = clLtGray;
                                        else if (table[i][j] == 19)Canvas->Brush->Color = cl3DLight;
                                        else if (table[i][j] == 20)Canvas->Brush->Color = clMoneyGreen;
                                        else if (table[i][j] == 99)Canvas->Brush->Color = clBlack;
                                        else if (table[i][j] == 200) Canvas->Brush->Color = 0xf442f1;
                                        else Canvas->Brush->Color = clWhite;

                                        Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                        }
               }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

        for (int i = 0; i <= 50; i++)
        {
                for (int j = 0; j <= 50; j++)
                {
                         if (energyTable[i][j] == energyInside)
                                        Canvas->Brush->Color = clBlue;

                               if (energyTable[i][j] == energyOnEdge)
                                     Canvas->Brush->Color = clLime;

                        if (energyTable[i][j] == 0)
                        {
                              Canvas->Brush->Color = clWhite;

                        }
                        Canvas->FillRect(Rect(i*10,j*10,i*10+10,j*10+10));
                }
        }
}
//---------------------------------------------------------------------------

