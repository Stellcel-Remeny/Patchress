VERSION 5.00
Begin VB.Form Prepare 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Ready to install"
   ClientHeight    =   7260
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   10170
   Enabled         =   0   'False
   Icon            =   "Prepare.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   7260
   ScaleWidth      =   10170
   ShowInTaskbar   =   0   'False
   Begin VB.PictureBox Picture4 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   -120
      Picture         =   "Prepare.frx":030A
      ScaleHeight     =   615
      ScaleWidth      =   10335
      TabIndex        =   2
      Top             =   6720
      Width           =   10335
      Begin VB.PictureBox Picture7 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   390
         Left            =   6480
         Picture         =   "Prepare.frx":12D9C
         ScaleHeight     =   390
         ScaleWidth      =   1155
         TabIndex        =   7
         Top             =   120
         Width           =   1155
         Begin VB.Label Label17 
            Alignment       =   2  'Center
            BackStyle       =   0  'Transparent
            Caption         =   "<<-- Back"
            Height          =   255
            Left            =   0
            TabIndex        =   8
            Top             =   120
            Width           =   1215
         End
      End
      Begin VB.PictureBox Picture6 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   390
         Left            =   7680
         Picture         =   "Prepare.frx":1456E
         ScaleHeight     =   390
         ScaleWidth      =   1155
         TabIndex        =   5
         Top             =   120
         Width           =   1155
         Begin VB.Label Label16 
            Alignment       =   2  'Center
            BackStyle       =   0  'Transparent
            Caption         =   "+ Install +"
            Height          =   255
            Left            =   0
            TabIndex        =   6
            Top             =   120
            Width           =   1215
         End
      End
      Begin VB.PictureBox Picture5 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   390
         Left            =   9000
         Picture         =   "Prepare.frx":15D40
         ScaleHeight     =   390
         ScaleWidth      =   1155
         TabIndex        =   3
         Top             =   120
         Width           =   1155
         Begin VB.Label Label9 
            Alignment       =   2  'Center
            BackStyle       =   0  'Transparent
            Caption         =   "Cancel"
            Height          =   255
            Left            =   0
            TabIndex        =   4
            Top             =   120
            Width           =   1215
         End
      End
      Begin VB.Label Label24 
         BackStyle       =   0  'Transparent
         Caption         =   "NTPatcher Version 6.0"
         Height          =   255
         Left            =   120
         TabIndex        =   10
         Top             =   360
         Width           =   2535
      End
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   855
      Left            =   -120
      Picture         =   "Prepare.frx":17512
      ScaleHeight     =   855
      ScaleWidth      =   10335
      TabIndex        =   0
      Top             =   0
      Width           =   10335
   End
   Begin VB.PictureBox Picture2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   5895
      Left            =   -120
      Picture         =   "Prepare.frx":35104
      ScaleHeight     =   5895
      ScaleWidth      =   2535
      TabIndex        =   1
      Top             =   840
      Width           =   2535
      Begin VB.Timer Timer1 
         Interval        =   1
         Left            =   240
         Top             =   5280
      End
   End
   Begin VB.PictureBox Picture8 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   5895
      Left            =   2400
      Picture         =   "Prepare.frx":65F1E
      ScaleHeight     =   5895
      ScaleWidth      =   7815
      TabIndex        =   9
      Top             =   840
      Width           =   7815
      Begin VB.CheckBox Check2 
         BackColor       =   &H00808080&
         Caption         =   "Startmenu Icon"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   375
         Left            =   4800
         TabIndex        =   12
         Top             =   3840
         Width           =   1695
      End
      Begin VB.CheckBox Check1 
         BackColor       =   &H00808080&
         Caption         =   "Desktop Shortcut"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   375
         Left            =   2640
         TabIndex        =   11
         Top             =   3840
         Width           =   1815
      End
   End
End
Attribute VB_Name = "Prepare"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Check1_Click()
  vars.CDeskIcon = Check1.Value
End Sub

Private Sub Check2_Click()
  vars.CStartIcon = Check2.Value
End Sub

Private Sub Form_Load()
  Me.Left = (BkgdWindow.Width - Me.Width) / 2
  Me.Top = (BkgdWindow.Height - Me.Height) / 2
  Check1.BackColor = RGB(170, 170, 170)
  Check2.BackColor = RGB(170, 170, 170)
  vars.CDeskIcon = "1"
  vars.CStartIcon = "1"
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Cancel = 1
  vars.AlrExit = "1"
  result = MsgBox("If you exit now, your changes will be discarded. Are you sure that you want to exit NTPatcher?", vbQuestion + vbYesNo, "Exit NTPatcher - Confirmation")
  If result = vbYes Then
    End
  Else
  End If
  vars.AlrExit = "0"
End Sub

Private Sub Label16_Click()
  Me.Enabled = False
  Me.Hide
  PInstall.Left = Me.Left
  PInstall.Top = Me.Top
  PInstall.Enabled = True
  PInstall.Show
End Sub

Private Sub Label17_Click()
  Me.Enabled = False
  Me.Hide
  InsType.Left = Me.Left
  InsType.Top = Me.Top
  InsType.Enabled = True
  InsType.Show
End Sub

Private Sub Label9_Click()
  Unload Me
End Sub

Private Sub Picture5_Click()
  Unload Me
End Sub

Private Sub Picture6_Click()
  Me.Enabled = False
  Me.Hide
  PInstall.Left = Me.Left
  PInstall.Top = Me.Top
  PInstall.Enabled = True
  PInstall.Show
End Sub

Private Sub Picture7_Click()
  Me.Enabled = False
  Me.Hide
  InsType.Left = Me.Left
  InsType.Top = Me.Top
  InsType.Enabled = True
  InsType.Show
End Sub

Private Sub Timer1_Timer()
  Timer1.Enabled = False
  If (vars.InsType = "1") Then
    Check1.Enabled = True
    Check1.Value = "1"
    Check2.Enabled = True
    Check2.Value = "1"
  ElseIf (vars.InsType = "2") Then
    Check1.Enabled = False
    Check1.Value = "0"
    Check2.Enabled = False
    Check2.Value = "0"
  End If
End Sub
