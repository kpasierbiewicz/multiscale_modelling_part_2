object Form1: TForm1
  Left = 276
  Top = 224
  Width = 868
  Height = 554
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 520
    Top = 24
    Width = 85
    Height = 13
    Caption = 'Amount nucleons:'
  end
  object Label2: TLabel
    Left = 520
    Top = 64
    Width = 26
    Height = 13
    Caption = 'Time:'
  end
  object Label3: TLabel
    Left = 520
    Top = 280
    Width = 92
    Height = 13
    Caption = 'Energy distrybution:'
  end
  object Label4: TLabel
    Left = 520
    Top = 320
    Width = 63
    Height = 13
    Caption = 'Energy insite:'
  end
  object Label5: TLabel
    Left = 520
    Top = 360
    Width = 78
    Height = 13
    Caption = 'Energy on edge:'
  end
  object Label6: TLabel
    Left = 520
    Top = 104
    Width = 20
    Height = 13
    Caption = 'Jgb:'
  end
  object Label7: TLabel
    Left = 520
    Top = 176
    Width = 46
    Height = 13
    Caption = 'Structure:'
  end
  object Label8: TLabel
    Left = 696
    Top = 280
    Width = 66
    Height = 13
    Caption = 'Nucleon type:'
  end
  object Label9: TLabel
    Left = 696
    Top = 320
    Width = 99
    Height = 13
    Caption = 'Nucleon dystribution:'
  end
  object Label10: TLabel
    Left = 696
    Top = 360
    Width = 69
    Height = 13
    Caption = 'Nucleons rate:'
  end
  object Label11: TLabel
    Left = 696
    Top = 400
    Width = 107
    Height = 13
    Caption = 'Recrystallization steps:'
  end
  object Label13: TLabel
    Left = 696
    Top = 176
    Width = 53
    Height = 13
    Caption = 'How many:'
  end
  object Label12: TLabel
    Left = 520
    Top = 216
    Width = 39
    Height = 13
    Caption = 'Method:'
  end
  object startSimulationButton: TButton
    Left = 712
    Top = 24
    Width = 113
    Height = 57
    Caption = 'START SIMULATION'
    TabOrder = 0
    OnClick = startSimulationButtonClick
  end
  object amountNucleonsComboBox: TComboBox
    Left = 520
    Top = 40
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = '2'
    Items.Strings = (
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12'
      '13'
      '14'
      '15'
      '16'
      '17'
      '18'
      '19'
      '20')
  end
  object timeEdit: TEdit
    Left = 520
    Top = 80
    Width = 145
    Height = 21
    TabOrder = 2
    Text = '5'
  end
  object clearAllButton: TButton
    Left = 712
    Top = 88
    Width = 113
    Height = 57
    Caption = 'CLEAR ALL'
    TabOrder = 3
    OnClick = clearAllButtonClick
  end
  object energyDistributionComboBox: TComboBox
    Left = 520
    Top = 296
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = 'Homogenous'
    Items.Strings = (
      'Homogenous'
      'Heterogenous')
  end
  object energyInsideEdit: TEdit
    Left = 520
    Top = 336
    Width = 145
    Height = 21
    TabOrder = 5
    Text = '2'
  end
  object energyOnEdgeEdit: TEdit
    Left = 520
    Top = 376
    Width = 145
    Height = 21
    TabOrder = 6
    Text = '5'
  end
  object showEnergyButton: TButton
    Left = 536
    Top = 408
    Width = 113
    Height = 25
    Caption = 'SHOW ENERGY'
    TabOrder = 7
    OnClick = showEnergyButtonClick
  end
  object jgbEdit: TEdit
    Left = 520
    Top = 120
    Width = 145
    Height = 21
    TabOrder = 8
    Text = '1,0'
  end
  object substructureTypeComboBox: TComboBox
    Left = 520
    Top = 192
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 9
    Text = 'Substructure'
    Items.Strings = (
      'Substructure'
      'Dual phase')
  end
  object generateSubstructureButton: TButton
    Left = 696
    Top = 224
    Width = 73
    Height = 33
    Caption = 'GENERATE'
    TabOrder = 10
    OnClick = generateSubstructureButtonClick
  end
  object nucleonTypeComboBox: TComboBox
    Left = 696
    Top = 296
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 11
    Text = 'Constans'
    Items.Strings = (
      'Constans'
      'Increasing')
  end
  object nucleonDystributionComboBox: TComboBox
    Left = 696
    Top = 336
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 12
    Text = 'On boundaries'
    Items.Strings = (
      'On boundaries'
      'Anywhere')
  end
  object nucleonRateEdit: TEdit
    Left = 696
    Top = 376
    Width = 145
    Height = 21
    TabOrder = 13
    Text = '2'
  end
  object recrystallizationStepsEdit: TEdit
    Left = 696
    Top = 416
    Width = 145
    Height = 21
    TabOrder = 14
    Text = '10'
  end
  object startRecrystallizationButton: TButton
    Left = 704
    Top = 456
    Width = 129
    Height = 41
    Caption = 'RECRYSTALLIZATION'
    TabOrder = 15
    OnClick = startRecrystallizationButtonClick
  end
  object howManyEdit: TEdit
    Left = 696
    Top = 192
    Width = 145
    Height = 21
    TabOrder = 16
    Text = '1'
  end
  object startStructureButton: TButton
    Left = 768
    Top = 224
    Width = 73
    Height = 33
    Caption = 'START'
    TabOrder = 17
    OnClick = startStructureButtonClick
  end
  object methodGenerateStructureComboBox: TComboBox
    Left = 520
    Top = 232
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 18
    Text = 'CA'
    Items.Strings = (
      'CA'
      'MC')
  end
  object Button1: TButton
    Left = 528
    Top = 440
    Width = 137
    Height = 25
    Caption = 'DISTRIBUTE ENERGY'
    TabOrder = 19
    OnClick = Button1Click
  end
  object Timer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = TimerTimer
    Left = 520
    Top = 472
  end
  object Timer2: TTimer
    Enabled = False
    Left = 552
    Top = 472
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer3Timer
    Left = 584
    Top = 472
  end
  object Timer4: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer4Timer
    Left = 616
    Top = 472
  end
  object Timer5: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer5Timer
    Left = 648
    Top = 472
  end
end
