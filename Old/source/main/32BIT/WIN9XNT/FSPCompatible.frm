VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Splash 
   BorderStyle     =   0  'None
   Caption         =   "Multipatcher"
   ClientHeight    =   4605
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   9240
   ControlBox      =   0   'False
   Icon            =   "FSPCompatible.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   4605
   ScaleWidth      =   9240
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin ComctlLib.ProgressBar ProgressBar1 
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   4440
      Width           =   9240
      _ExtentX        =   16298
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   0
      Max             =   175
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   4575
      Left            =   0
      Picture         =   "FSPCompatible.frx":030A
      ScaleHeight     =   4575
      ScaleWidth      =   9375
      TabIndex        =   0
      Top             =   0
      Width           =   9375
      Begin VB.Timer Timer2 
         Enabled         =   0   'False
         Interval        =   1
         Left            =   480
         Top             =   120
      End
      Begin VB.Timer Timer3 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   840
         Top             =   120
      End
      Begin VB.Timer Timer1 
         Interval        =   1
         Left            =   120
         Top             =   120
      End
      Begin VB.Label Label7 
         BackStyle       =   0  'Transparent
         Caption         =   "Stellcel Remeny"
         BeginProperty Font 
            Name            =   "System"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   3600
         Width           =   3255
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         Caption         =   "Multipatcher Version 0.1"
         BeginProperty Font 
            Name            =   "System"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   6000
         TabIndex        =   5
         Top             =   120
         Width           =   3135
      End
      Begin VB.Label Label3 
         BackStyle       =   0  'Transparent
         Caption         =   "%"
         BeginProperty Font 
            Name            =   "System"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   1200
         TabIndex        =   4
         Top             =   4080
         Width           =   615
      End
      Begin VB.Label Label2 
         BackStyle       =   0  'Transparent
         Caption         =   "Progress:"
         BeginProperty Font 
            Name            =   "System"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   4080
         Width           =   1095
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "Processing Configuration..."
         BeginProperty Font 
            Name            =   "System"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   3840
         Width           =   3255
      End
   End
End
Attribute VB_Name = "Splash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
  'Me.Top = (Screen.Height - FormSplash.Height) / 2
  Screen.MousePointer = vbArrowHourglass
  i = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Cancel = 1
End Sub

Private Sub Picture1_Click()

End Sub

Private Sub Timer1_Timer()
  Timer1.Enabled = False
  If (i < "100") Then
    i = i + 4
    Label3.Caption = i & "%"
    ProgressBar1.Value = i
    Timer1.Enabled = True
  Else
    If IsWindowsXPOrServer2003 = False Then
      Me.Enabled = False
      Me.Hide
      result = MsgBox("This program requires Windows XP or Server 2003 that has an NT Version of 5.1.", vbCritical + vbOKOnly)
      End
    Else
      Me.Enabled = False
      Me.Hide
      result = MsgBox("One or more files that are required by NTPatcher were not found. NTPatcher cannot continue.", vbCritical + vbOKOnly)
      End
    End If
  End If
End Sub

Private Sub Timer3_Timer()
  Timer3.Enabled = False
  Me.Enabled = False
  Me.Hide
  Screen.MousePointer = vbNormal
  BkgdWindow.Enabled = True
  BkgdWindow.Show
  Exit Sub
End Sub

Private Sub Timer2_Timer()
  Timer2.Enabled = False
  If (i = "100") Then
    Screen.MousePointer = vbHourglass
    Label1.Caption = "Loading NTPatcher..."
    Label2.Visible = False
    Label3.Visible = False
    Label7.Top = Label1.Top
    Label1.Top = Label2.Top
  End If
  If (i < "175") Then
    i = i + 3
    ProgressBar1.Value = i
    'If (((i - 100) + 15) < 101) Then
    If ((i - 100) < 100) Then
      Label1.Caption = "Loading NTPatcher... " & (i - 100) '+ 15
    End If
    Timer2.Enabled = True
  Else
    Me.Enabled = False
    Me.Hide
    Timer3.Enabled = True
  End If
End Sub
