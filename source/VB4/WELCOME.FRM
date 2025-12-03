VERSION 4.00
Begin VB.Form welcome 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Welcome to MultiPatcher"
   ClientHeight    =   6045
   ClientLeft      =   4575
   ClientTop       =   3570
   ClientWidth     =   8955
   Height          =   6555
   Left            =   4515
   LinkTopic       =   "main"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "WELCOME.frx":0000
   ScaleHeight     =   6045
   ScaleWidth      =   8955
   Top             =   3120
   WhatsThisHelp   =   -1  'True
   Width           =   9075
   Begin VB.CommandButton NT351 
      Caption         =   "Windows NT 3.51"
      Height          =   735
      Left            =   3240
      TabIndex        =   13
      Top             =   3840
      Width           =   1095
   End
   Begin VB.CommandButton W31 
      Caption         =   "Windows 3.1"
      Height          =   735
      Left            =   1800
      TabIndex        =   5
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton WXP 
      Caption         =   "Windows XP"
      Height          =   735
      Left            =   7560
      TabIndex        =   14
      Top             =   3840
      Width           =   1095
   End
   Begin VB.CommandButton NT35 
      Caption         =   "Windows NT 3.5"
      Height          =   735
      Left            =   1800
      TabIndex        =   12
      Top             =   3840
      Width           =   1095
   End
   Begin VB.CommandButton NT4 
      Caption         =   "Windows NT 4.0"
      Height          =   735
      Left            =   4680
      TabIndex        =   11
      Top             =   3840
      Width           =   1095
   End
   Begin VB.CommandButton W2K 
      Caption         =   "Windows 2000"
      Height          =   735
      Left            =   6120
      TabIndex        =   10
      Top             =   3840
      Width           =   1095
   End
   Begin VB.CommandButton NT31 
      Caption         =   "Windows NT 3.1"
      Height          =   735
      Left            =   360
      TabIndex        =   9
      Top             =   3840
      Width           =   1095
   End
   Begin VB.CommandButton WME 
      Caption         =   "Windows Me"
      Height          =   735
      Left            =   6120
      TabIndex        =   8
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton W98 
      Caption         =   "Windows 98"
      Height          =   735
      Left            =   4680
      TabIndex        =   7
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton W95 
      Caption         =   "Windows 95"
      Height          =   735
      Left            =   3240
      TabIndex        =   6
      Top             =   4920
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      BackColor       =   &H00C0C0C0&
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   1695
      Left            =   1560
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      TabIndex        =   4
      Text            =   "WELCOME.frx":B18E2
      Top             =   1800
      Width           =   5895
   End
   Begin VB.Timer starttimer 
      Interval        =   1
      Left            =   8400
      Top             =   120
   End
   Begin VB.CommandButton startbutton 
      Caption         =   "Start"
      Default         =   -1  'True
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      MousePointer    =   1  'Arrow
      TabIndex        =   1
      Top             =   5640
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Exit"
      Height          =   375
      Left            =   7800
      TabIndex        =   0
      Top             =   5640
      Width           =   1095
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "vbGUI: 1.0, VB4"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   0
      TabIndex        =   15
      Top             =   0
      Width           =   1455
   End
   Begin VB.Label startlabel 
      BackStyle       =   0  'Transparent
      Caption         =   "<-- Click here to begin"
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   400
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   8640
      TabIndex        =   3
      Top             =   5640
      Visible         =   0   'False
      Width           =   3135
   End
   Begin VB.Label OSLabel 
      BackStyle       =   0  'Transparent
      Caption         =   "Welcome to MultiPatcher!"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   495
      Left            =   1440
      TabIndex        =   2
      Top             =   1320
      Width           =   3495
   End
End
Attribute VB_Name = "welcome"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

'
Sub enableAllButtons()
    NT31.Enabled = True
    NT35.Enabled = True
    NT351.Enabled = True
    NT4.Enabled = True
    W2K.Enabled = True
    WXP.Enabled = True
    W31.Enabled = True
    W95.Enabled = True
    W98.Enabled = True
    WME.Enabled = True
End Sub


Private Sub Command2_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Debug.Print ""
    Debug.Print "NEW SESSION"
    'Center Window
    Me.Left = (Screen.Width - Me.Width) \ 2
    Me.Top = (Screen.Height - Me.Height) \ 2
    ' Play startup sound
    Debug.Print "Playing VBBEGIN.WAV"
    Dim s$
    s = App.Path & "\DATA\VBBEGIN.WAV"
    PlayWavAsync s
End Sub


Private Sub Form_Unload(Cancel As Integer)
    StopWav
End Sub


Private Sub NT31_Click()
    WinVer = "nt31"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub

Private Sub NT35_Click()
    WinVer = "nt35"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


Private Sub NT351_Click()
    WinVer = "nt351"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


Private Sub NT4_Click()
    WinVer = "nt4"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


Private Sub startbutton_Click()
    If Not WinVer = "" Then
        StopWav
        main.Enabled = True
        main.Visible = True
        Load main
        Unload Me
    End If
End Sub

Private Sub starttimer_Timer()
    If startlabel.Left > 1250 Then
        startlabel.Left = startlabel.Left - 200
    Else
        starttimer.Enabled = False
    End If
End Sub


Private Sub W2K_Click()
    WinVer = "w2k"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


Private Sub W31_Click()
    WinVer = "w31"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub

Private Sub W95_Click()
    WinVer = "w95"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


Private Sub W98_Click()
    WinVer = "w98"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


Private Sub WME_Click()
    WinVer = "wme"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


Private Sub WXP_Click()
    WinVer = "wxp"
    main.Enabled = True
    main.Visible = True
    Load main
    Unload Me
End Sub


