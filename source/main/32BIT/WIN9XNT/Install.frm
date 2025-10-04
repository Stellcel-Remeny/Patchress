VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Install 
   BackColor       =   &H00404040&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Installing NTPatcher"
   ClientHeight    =   1965
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4815
   ControlBox      =   0   'False
   Icon            =   "Install.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   1965
   ScaleWidth      =   4815
   ShowInTaskbar   =   0   'False
   Begin VB.Timer Timer11 
      Interval        =   15
      Left            =   240
      Top             =   120
   End
   Begin VB.Timer Timer10 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   1080
      Top             =   1560
   End
   Begin VB.Timer Timer9 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   1440
      Top             =   1560
   End
   Begin VB.Timer Timer8 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   1800
      Top             =   1560
   End
   Begin VB.Timer Timer7 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   2160
      Top             =   1560
   End
   Begin VB.Timer Timer6 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   2520
      Top             =   1560
   End
   Begin VB.Timer Timer5 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   2880
      Top             =   1560
   End
   Begin VB.Timer Timer4 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   3240
      Top             =   1560
   End
   Begin VB.Timer Timer3 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   3600
      Top             =   1560
   End
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   150
      Left            =   3960
      Top             =   1560
   End
   Begin VB.Timer Timer1 
      Interval        =   150
      Left            =   4320
      Top             =   1560
   End
   Begin ComctlLib.ProgressBar ProgressBar1 
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1320
      Width           =   4575
      _ExtentX        =   8070
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   0
   End
   Begin VB.Label Label4 
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   720
      TabIndex        =   3
      Top             =   720
      Width           =   3975
   End
   Begin VB.Label Label3 
      BackStyle       =   0  'Transparent
      Caption         =   "To:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   720
      Width           =   495
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   1440
      TabIndex        =   1
      Top             =   240
      Width           =   3255
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Copying:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
End
Attribute VB_Name = "Install"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Picture1_Click()

End Sub

Private Sub Form_Load()
  Me.BackColor = RGB(28, 78, 153)
  Me.Left = (BkgdWindow.Width - Me.Width) / 1.014
  Me.Top = (BkgdWindow.Height - Me.Height) / 1.1
  Label4.Caption = vars.InsPath
End Sub

Private Sub Timer1_Timer()
  Timer1.Enabled = False
  Label2.Caption = "Windows NT 3.1 Loaders"
  Shell "CMD.EXE /c ""copy .\1? " & vars.InsPath & "NTPatcher\1\.""", vbHide
  'ProgressBar1.Value = 11
  Timer2.Enabled = True
End Sub

Private Sub Timer10_Timer()
  'ProgressBar1.Value = 100
  Timer10.Enabled = False
  Me.Enabled = False
  Me.Hide
  SysUpd.Enabled = True
  SysUpd.Show
End Sub

Private Sub Timer11_Timer()
  Timer11.Enabled = False
  If (ProgressBar1.Value < "100") Then
    ProgressBar1.Value = ProgressBar1.Value + "1"
    Timer11.Enabled = True
  End If
End Sub

Private Sub Timer2_Timer()
  Timer2.Enabled = False
  Label2.Caption = "Windows NT 3.5 Loaders"
  Shell "CMD.EXE /c ""copy .\2? " & vars.InsPath & "NTPatcher\2\.""", vbHide
  'ProgressBar1.Value = 22
  Timer3.Enabled = True
End Sub

Private Sub Timer3_Timer()
  Timer3.Enabled = False
  Label2.Caption = "Windows NT 3.51 Loaders"
  Shell "CMD.EXE /c ""copy .\3? " & vars.InsPath & "NTPatcher\3\.""", vbHide
  'ProgressBar1.Value = 33
  Timer4.Enabled = True
End Sub

Private Sub Timer4_Timer()
  Timer4.Enabled = False
  Label2.Caption = "Windows NT 4.0 Loaders"
  Shell "CMD.EXE /c ""copy .\4? " & vars.InsPath & "NTPatcher\4\.""", vbHide
  'ProgressBar1.Value = 44
  Timer5.Enabled = True
End Sub

Private Sub Timer5_Timer()
  Timer5.Enabled = False
  Label2.Caption = "Windows 2000 Loaders"
  Shell "CMD.EXE /c ""copy .\5? " & vars.InsPath & "NTPatcher\5\.""", vbHide
  'ProgressBar1.Value = 55
  Timer6.Enabled = True
End Sub

Private Sub Timer6_Timer()
  Timer6.Enabled = False
  Label2.Caption = "Windows XP Loaders"
  Shell "CMD.EXE /c ""copy .\6? " & vars.InsPath & "NTPatcher\6\.""", vbHide
  'ProgressBar1.Value = 66
  Timer7.Enabled = True
End Sub

Private Sub Timer7_Timer()
  Timer7.Enabled = False
  Label2.Caption = "Toolkit Program"
  Shell "CMD.EXE /c ""copy .\BTRE.CFG " & vars.InsPath & "NTPatcher\Toolkit.exe""", vbHide
  'ProgressBar1.Value = 77
  Timer8.Enabled = True
End Sub

Private Sub Timer8_Timer()
  Timer8.Enabled = False
  Label2.Caption = "Side Loaders"
  Shell "CMD.EXE /c ""copy .\LOWLD1.CFG " & vars.InsPath & "BXTC1.DAT""", vbHide
  Shell "CMD.EXE /c ""copy .\LOWLD2.CFG " & vars.InsPath & "BXTC2.DAT""", vbHide
  Shell "CMD.EXE /c ""copy .\LOWLD3.CFG " & vars.InsPath & "BXTC3.DAT""", vbHide
  Shell "CMD.EXE /c ""copy .\LOWLD4.CFG " & vars.InsPath & "BXTC4.DAT""", vbHide
  Shell "CMD.EXE /c ""copy .\LOWLD5.CFG " & vars.InsPath & "BXTC5.DAT""", vbHide
  Shell "CMD.EXE /c ""copy .\LOWLD6.CFG " & vars.InsPath & "BXTC6.DAT""", vbHide
  Shell "CMD.EXE /c ""copy .\LOWLD7.CFG " & vars.InsPath & "BXTC7.DAT""", vbHide
  Shell "CMD.EXE /c ""copy .\LOWLD8.CFG " & vars.InsPath & "BXTC8.DAT""", vbHide
  'ProgressBar1.Value = 88
  Timer9.Enabled = True
End Sub

Private Sub Timer9_Timer()
  Timer9.Enabled = False
  Label2.Caption = "Default Boot Data"
  'BOOT.INI
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N01""", vbHide
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N02""", vbHide
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N03""", vbHide
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N04""", vbHide
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N05""", vbHide
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N06""", vbHide
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N07""", vbHide
  Shell "CMD.EXE /c ""copy .\PS.CFG " & vars.InsPath & "MTMP.N08""", vbHide
  'NTLDR
  Shell "CMD.EXE /c ""copy .\51 " & vars.InsPath & "PTCN1""", vbHide
  Shell "CMD.EXE /c ""copy .\52 " & vars.InsPath & "PTCN2""", vbHide
  Shell "CMD.EXE /c ""copy .\53 " & vars.InsPath & "PTCN3""", vbHide
  Shell "CMD.EXE /c ""copy .\54 " & vars.InsPath & "PTCN4""", vbHide
  Shell "CMD.EXE /c ""copy .\55 " & vars.InsPath & "PTCN5""", vbHide
  Shell "CMD.EXE /c ""copy .\56 " & vars.InsPath & "PTCN6""", vbHide
  Shell "CMD.EXE /c ""copy .\57 " & vars.InsPath & "PTCN7""", vbHide
  Shell "CMD.EXE /c ""copy .\58 " & vars.InsPath & "PTCN8""", vbHide
  'ProgressBar1.Value = 99
  Timer10.Enabled = True
End Sub
