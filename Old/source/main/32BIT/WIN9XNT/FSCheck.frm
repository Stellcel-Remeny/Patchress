VERSION 5.00
Begin VB.Form FSCheck 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Verifying Files"
   ClientHeight    =   7260
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   10170
   Enabled         =   0   'False
   Icon            =   "FSCheck.frx":0000
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
      Picture         =   "FSCheck.frx":030A
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
         Enabled         =   0   'False
         ForeColor       =   &H80000008&
         Height          =   390
         Left            =   6480
         Picture         =   "FSCheck.frx":12D9C
         ScaleHeight     =   390
         ScaleWidth      =   1155
         TabIndex        =   7
         Top             =   120
         Width           =   1155
         Begin VB.Label Label17 
            Alignment       =   2  'Center
            BackStyle       =   0  'Transparent
            Caption         =   "<<-- Back"
            Enabled         =   0   'False
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
         Enabled         =   0   'False
         ForeColor       =   &H80000008&
         Height          =   390
         Left            =   7680
         Picture         =   "FSCheck.frx":1456E
         ScaleHeight     =   390
         ScaleWidth      =   1155
         TabIndex        =   5
         Top             =   120
         Width           =   1155
         Begin VB.Label Label16 
            Alignment       =   2  'Center
            BackStyle       =   0  'Transparent
            Caption         =   "Next -->>"
            Enabled         =   0   'False
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
         Enabled         =   0   'False
         ForeColor       =   &H80000008&
         Height          =   390
         Left            =   9000
         Picture         =   "FSCheck.frx":15D40
         ScaleHeight     =   390
         ScaleWidth      =   1155
         TabIndex        =   3
         Top             =   120
         Width           =   1155
         Begin VB.Label Label9 
            Alignment       =   2  'Center
            BackStyle       =   0  'Transparent
            Caption         =   "Cancel"
            Enabled         =   0   'False
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
      Picture         =   "FSCheck.frx":17512
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
      Picture         =   "FSCheck.frx":35104
      ScaleHeight     =   5895
      ScaleWidth      =   2535
      TabIndex        =   1
      Top             =   840
      Width           =   2535
      Begin VB.Timer Timer6 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   1680
         Top             =   5280
      End
      Begin VB.Timer Timer0 
         Interval        =   1
         Left            =   240
         Top             =   3840
      End
      Begin VB.Timer Timer5 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   1200
         Top             =   5280
      End
      Begin VB.Timer Timer4 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   1200
         Top             =   4800
      End
      Begin VB.Timer Timer3 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   720
         Top             =   4800
      End
      Begin VB.Timer Timer2 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   720
         Top             =   4320
      End
      Begin VB.Timer Timer1 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   240
         Top             =   4320
      End
   End
   Begin VB.PictureBox Picture8 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   5895
      Left            =   2400
      Picture         =   "FSCheck.frx":65F1E
      ScaleHeight     =   5895
      ScaleWidth      =   7815
      TabIndex        =   9
      Top             =   840
      Width           =   7815
      Begin VB.Label Label29 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "Previous Installation"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   840
         TabIndex        =   22
         Top             =   5280
         Visible         =   0   'False
         Width           =   2295
      End
      Begin VB.Label Label28 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "In Queue"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   3360
         TabIndex        =   21
         Top             =   5280
         Visible         =   0   'False
         Width           =   2055
      End
      Begin VB.Label Label26 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "no value"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   5640
         TabIndex        =   20
         Top             =   5280
         Visible         =   0   'False
         Width           =   1215
      End
      Begin VB.Label Label20 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "NTLDR"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   840
         TabIndex        =   19
         Top             =   4320
         Width           =   2295
      End
      Begin VB.Label Label19 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "NTDETECT.COM"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   840
         TabIndex        =   18
         Top             =   4800
         Width           =   2295
      End
      Begin VB.Label Label18 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "BOOT.INI"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   840
         TabIndex        =   17
         Top             =   3840
         Width           =   2295
      End
      Begin VB.Label Label13 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "In Queue"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   3360
         TabIndex        =   16
         Top             =   3840
         Width           =   2055
      End
      Begin VB.Label Label10 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "In Queue"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   3360
         TabIndex        =   15
         Top             =   4320
         Width           =   2055
      End
      Begin VB.Label Label12 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "In Queue"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   3360
         TabIndex        =   14
         Top             =   4800
         Width           =   2055
      End
      Begin VB.Label Label14 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "no value"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   5640
         TabIndex        =   13
         Top             =   3840
         Width           =   1215
      End
      Begin VB.Label Label15 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "no value"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   5640
         TabIndex        =   12
         Top             =   4320
         Width           =   1215
      End
      Begin VB.Label Label7 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "no value"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   5640
         TabIndex        =   11
         Top             =   4800
         Width           =   1215
      End
   End
End
Attribute VB_Name = "FSCheck"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim fso As New FileSystemObject
Dim result As VbMsgBoxResult

Private Sub Form_Load()
  Me.Left = (BkgdWindow.Width - Me.Width) / 2
  Me.Top = (BkgdWindow.Height - Me.Height) / 2
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Cancel = 1
End Sub

Private Sub Label17_Click()
  Me.Enabled = False
  Me.Hide
  PathInput.Left = Me.Left
  PathInput.Top = Me.Top
  PathInput.Enabled = True
  PathInput.Show
End Sub

Private Sub Label9_Click()
  Unload Me
End Sub

Private Sub Picture5_Click()
  Unload Me
End Sub

Private Sub Picture7_Click()
  Me.Enabled = False
  Me.Hide
  PathInput.Left = Me.Left
  PathInput.Top = Me.Top
  PathInput.Enabled = True
  PathInput.Show
End Sub

Private Sub Timer0_Timer()
  Timer0.Enabled = False
  vars.AlrExit = "1"
  vars.ErrOcc = "0"
  Label14.Caption = "no value"
  Label15.Caption = "no value"
  Label7.Caption = "no value"
  Label26.Caption = "no value"
  Label13.Caption = "In Queue"
  Label10.Caption = "In Queue"
  Label12.Caption = "In Queue"
  Label28.Caption = "In Queue"
  Timer1.Enabled = True
End Sub

Private Sub Timer1_Timer()
  Timer1.Enabled = False
  Label13.Caption = "Wait"
  Label14.Caption = "no value"
  Label15.Caption = "no value"
  Label7.Caption = "no value"
  Label26.Caption = "no value"
  Label10.Caption = "In Queue"
  Label12.Caption = "In Queue"
  Label28.Caption = "In Queue"
  'Enable current labels
  Label18.Enabled = True
  Label13.Enabled = True
  Label14.Enabled = True
  Label13.Caption = "Wait"
  'Disable labels
  Label20.Enabled = False
  Label19.Enabled = False
  Label29.Enabled = False
  Label10.Enabled = False
  Label12.Enabled = False
  Label28.Enabled = False
  Label15.Enabled = False
  Label7.Enabled = False
  Label26.Enabled = False
  Timer2.Enabled = True
End Sub

Private Sub Timer2_Timer()
  Timer2.Enabled = False
  Label13.Caption = "Done"
  Label10.Caption = "Wait"
  If fso.FileExists(vars.InsPath & "BOOT.INI") Then
    Label14.Caption = "True"
  Else
    Label14.Caption = "False"
    vars.ErrOcc = "1"
  End If
  Label18.Enabled = False
  Label13.Enabled = False
  Label14.Enabled = False
  Label20.Enabled = True
  Label10.Enabled = True
  Label15.Enabled = True
  Timer3.Enabled = True
End Sub

Private Sub Timer3_Timer()
  Timer3.Enabled = False
  Label10.Caption = "Done"
  Label12.Caption = "Wait"
  If fso.FileExists(vars.InsPath & "NTLDR") Then
    Label15.Caption = "True"
  Else
    Label15.Caption = "False"
    vars.ErrOcc = "1"
  End If
  Label20.Enabled = False
  Label10.Enabled = False
  Label15.Enabled = False
  Label19.Enabled = True
  Label12.Enabled = True
  Label7.Enabled = True
  Timer4.Enabled = True
End Sub

Private Sub Timer4_Timer()
  Timer4.Enabled = False
  Label12.Caption = "Done"
  Label28.Caption = "Wait"
  If fso.FileExists(vars.InsPath & "NTDETECT.COM") Then
    Label7.Caption = "True"
  Else
    Label7.Caption = "False"
    vars.ErrOcc = "1"
  End If
  Label19.Enabled = False
  Label12.Enabled = False
  Label7.Enabled = False
  Label29.Enabled = True
  Label28.Enabled = True
  Label26.Enabled = True
  Timer5.Enabled = True
End Sub

Private Sub Timer5_Timer()
  Timer5.Enabled = False
  Label28.Caption = "Done"
  If fso.FileExists(vars.InsPath & "Toolkit.exe") Then
    Label26.Caption = "True"
    vars.upgrade = "1"
  Else
    Label26.Caption = "False"
    vars.upgrade = "0"
  End If
  Label29.Enabled = False
  Label28.Enabled = False
  Label26.Enabled = False
  Timer6.Enabled = True
End Sub

Private Sub Timer6_Timer()
  Timer6.Enabled = False
  If (vars.ErrOcc = "1") Then
    result = MsgBox("One or more bootfiles were not found in the drive that you specified. Please choose another directory that has the specified files: ""BOOT.INI"", ""NTLDR"", ""NTDETECT.COM"".", vbExclamation + vbOKOnly)
    Me.Enabled = False
    Me.Hide
    vars.AlrExit = "0"
    PathInput.Left = Me.Left
    PathInput.Top = Me.Top
    PathInput.Enabled = True
    PathInput.Show
  Else
    Me.Enabled = False
    Me.Hide
    vars.AlrExit = "0"
    InsType.Left = Me.Left
    InsType.Top = Me.Top
    InsType.Enabled = True
    InsType.Show
    'Prepare.Left = Me.Left
    'Prepare.Top = Me.Top
    'Prepare.Enabled = True
    'Prepare.Show
  End If
End Sub
