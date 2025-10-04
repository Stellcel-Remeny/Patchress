VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form PInstall 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Preparing Installation"
   ClientHeight    =   7260
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   10170
   Enabled         =   0   'False
   Icon            =   "PInstall.frx":0000
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
      Picture         =   "PInstall.frx":030A
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
         Picture         =   "PInstall.frx":12D9C
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
         Picture         =   "PInstall.frx":1456E
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
         Picture         =   "PInstall.frx":15D40
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
      Picture         =   "PInstall.frx":17512
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
      Picture         =   "PInstall.frx":35104
      ScaleHeight     =   5895
      ScaleWidth      =   2535
      TabIndex        =   1
      Top             =   840
      Width           =   2535
      Begin VB.Timer Timer2 
         Enabled         =   0   'False
         Interval        =   300
         Left            =   840
         Top             =   5160
      End
      Begin VB.Timer Timer1 
         Interval        =   1
         Left            =   360
         Top             =   5160
      End
   End
   Begin VB.PictureBox Picture8 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   5895
      Left            =   2400
      Picture         =   "PInstall.frx":65F1E
      ScaleHeight     =   5895
      ScaleWidth      =   7815
      TabIndex        =   9
      Top             =   840
      Width           =   7815
      Begin ComctlLib.ProgressBar ProgressBar1 
         Height          =   375
         Left            =   240
         TabIndex        =   11
         Top             =   5040
         Width           =   7215
         _ExtentX        =   12726
         _ExtentY        =   661
         _Version        =   327682
         Appearance      =   0
      End
      Begin VB.Label Label10 
         BackStyle       =   0  'Transparent
         Caption         =   "%"
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
         Height          =   375
         Left            =   1320
         TabIndex        =   12
         Top             =   4560
         Width           =   615
      End
   End
End
Attribute VB_Name = "PInstall"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim i As Integer
Dim fso As New FileSystemObject

Function DirectoryExists(directoryPath As String) As Boolean
    If Dir(directoryPath, vbDirectory) <> "" Then
        DirectoryExists = True
    Else
        DirectoryExists = False
    End If
End Function

Private Sub Form_Load()
  Me.Left = (BkgdWindow.Width - Me.Width) / 2
  Me.Top = (BkgdWindow.Height - Me.Height) / 2
  vars.AlrExit = "1"
  i = 0
  Screen.MousePointer = vbHourglass
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

Private Sub Timer1_Timer()
  Timer1.Enabled = False
  If (i < "100") Then
    i = i + 4
    Label10.Caption = i & "%"
    ProgressBar1.Value = i
    Timer1.Enabled = True
  Else
   If (vars.InsType = "2") Then
    If fso.FileExists(vars.InsPath & "ntldr.bak") Then SetAttr vars.InsPath & "ntldr.bak", vbNormal
    If fso.FileExists(vars.InsPath & "ntldr.bak") Then Kill (vars.InsPath & "ntldr.bak")
    Open ".\NTPATCH.INI" For Output As #1
      Print #1, vars.InsPath
    Close #1
   End If
   If (vars.InsType = "1") Then
    'If file_exist
    If fso.FileExists(vars.InsPath & "boot.bak") Then SetAttr vars.InsPath & "boot.bak", vbNormal
    If fso.FileExists(vars.InsPath & "boot.bak") Then Kill (vars.InsPath & "boot.bak")
    FileCopy vars.InsPath & "boot.ini", vars.InsPath & "boot.bak"

    If fso.FileExists(vars.InsPath & "mtmp.n01") Then SetAttr vars.InsPath & "mtmp.n01", vbNormal
    If fso.FileExists(vars.InsPath & "mtmp.n02") Then SetAttr vars.InsPath & "mtmp.n02", vbNormal
    If fso.FileExists(vars.InsPath & "mtmp.n03") Then SetAttr vars.InsPath & "mtmp.n03", vbNormal
    If fso.FileExists(vars.InsPath & "mtmp.n04") Then SetAttr vars.InsPath & "mtmp.n04", vbNormal
    If fso.FileExists(vars.InsPath & "mtmp.n05") Then SetAttr vars.InsPath & "mtmp.n05", vbNormal
    If fso.FileExists(vars.InsPath & "mtmp.n06") Then SetAttr vars.InsPath & "mtmp.n06", vbNormal
    If fso.FileExists(vars.InsPath & "mtmp.n07") Then SetAttr vars.InsPath & "mtmp.n07", vbNormal
    If fso.FileExists(vars.InsPath & "mtmp.n08") Then SetAttr vars.InsPath & "mtmp.n08", vbNormal

    If fso.FileExists(vars.InsPath & "ptcn1") Then SetAttr vars.InsPath & "ptcn1", vbNormal
    If fso.FileExists(vars.InsPath & "ptcn2") Then SetAttr vars.InsPath & "ptcn2", vbNormal
    If fso.FileExists(vars.InsPath & "ptcn3") Then SetAttr vars.InsPath & "ptcn3", vbNormal
    If fso.FileExists(vars.InsPath & "ptcn4") Then SetAttr vars.InsPath & "ptcn4", vbNormal
    If fso.FileExists(vars.InsPath & "ptcn5") Then SetAttr vars.InsPath & "ptcn5", vbNormal
    If fso.FileExists(vars.InsPath & "ptcn6") Then SetAttr vars.InsPath & "ptcn6", vbNormal
    If fso.FileExists(vars.InsPath & "ptcn7") Then SetAttr vars.InsPath & "ptcn7", vbNormal
    If fso.FileExists(vars.InsPath & "ptcn8") Then SetAttr vars.InsPath & "ptcn8", vbNormal

    If fso.FileExists(vars.InsPath & "bxtc1.dat") Then SetAttr vars.InsPath & "bxtc1.dat", vbNormal
    If fso.FileExists(vars.InsPath & "bxtc2.dat") Then SetAttr vars.InsPath & "bxtc2.dat", vbNormal
    If fso.FileExists(vars.InsPath & "bxtc3.dat") Then SetAttr vars.InsPath & "bxtc3.dat", vbNormal
    If fso.FileExists(vars.InsPath & "bxtc4.dat") Then SetAttr vars.InsPath & "bxtc4.dat", vbNormal
    If fso.FileExists(vars.InsPath & "bxtc5.dat") Then SetAttr vars.InsPath & "bxtc5.dat", vbNormal
    If fso.FileExists(vars.InsPath & "bxtc6.dat") Then SetAttr vars.InsPath & "bxtc6.dat", vbNormal
    If fso.FileExists(vars.InsPath & "bxtc7.dat") Then SetAttr vars.InsPath & "bxtc7.dat", vbNormal
    If fso.FileExists(vars.InsPath & "bxtc8.dat") Then SetAttr vars.InsPath & "bxtc8.dat", vbNormal

    'File Del
    If fso.FileExists(vars.InsPath & "mtmp.n01") Then Kill (vars.InsPath & "mtmp.n01")
    If fso.FileExists(vars.InsPath & "mtmp.n02") Then Kill (vars.InsPath & "mtmp.n02")
    If fso.FileExists(vars.InsPath & "mtmp.n03") Then Kill (vars.InsPath & "mtmp.n03")
    If fso.FileExists(vars.InsPath & "mtmp.n04") Then Kill (vars.InsPath & "mtmp.n04")
    If fso.FileExists(vars.InsPath & "mtmp.n05") Then Kill (vars.InsPath & "mtmp.n05")
    If fso.FileExists(vars.InsPath & "mtmp.n06") Then Kill (vars.InsPath & "mtmp.n06")
    If fso.FileExists(vars.InsPath & "mtmp.n07") Then Kill (vars.InsPath & "mtmp.n07")
    If fso.FileExists(vars.InsPath & "mtmp.n08") Then Kill (vars.InsPath & "mtmp.n08")
  
    If fso.FileExists(vars.InsPath & "ptcn1") Then Kill (vars.InsPath & "ptcn1")
    If fso.FileExists(vars.InsPath & "ptcn2") Then Kill (vars.InsPath & "ptcn2")
    If fso.FileExists(vars.InsPath & "ptcn3") Then Kill (vars.InsPath & "ptcn3")
    If fso.FileExists(vars.InsPath & "ptcn4") Then Kill (vars.InsPath & "ptcn4")
    If fso.FileExists(vars.InsPath & "ptcn5") Then Kill (vars.InsPath & "ptcn5")
    If fso.FileExists(vars.InsPath & "ptcn6") Then Kill (vars.InsPath & "ptcn6")
    If fso.FileExists(vars.InsPath & "ptcn7") Then Kill (vars.InsPath & "ptcn7")
    If fso.FileExists(vars.InsPath & "ptcn8") Then Kill (vars.InsPath & "ptcn8")
  
    If fso.FileExists(vars.InsPath & "bxtc1.dat") Then Kill (vars.InsPath & "bxtc1.dat")
    If fso.FileExists(vars.InsPath & "bxtc2.dat") Then Kill (vars.InsPath & "bxtc2.dat")
    If fso.FileExists(vars.InsPath & "bxtc3.dat") Then Kill (vars.InsPath & "bxtc3.dat")
    If fso.FileExists(vars.InsPath & "bxtc4.dat") Then Kill (vars.InsPath & "bxtc4.dat")
    If fso.FileExists(vars.InsPath & "bxtc5.dat") Then Kill (vars.InsPath & "bxtc5.dat")
    If fso.FileExists(vars.InsPath & "bxtc6.dat") Then Kill (vars.InsPath & "bxtc6.dat")
    If fso.FileExists(vars.InsPath & "bxtc7.dat") Then Kill (vars.InsPath & "bxtc7.dat")
    If fso.FileExists(vars.InsPath & "bxtc8.dat") Then Kill (vars.InsPath & "bxtc8.dat")
    
    If DirectoryExists(vars.InsPath & "NTPatcher") Then
      Kill (vars.InsPath & "NTPatcher\1\*.*")
      Kill (vars.InsPath & "NTPatcher\2\*.*")
      Kill (vars.InsPath & "NTPatcher\3\*.*")
      Kill (vars.InsPath & "NTPatcher\4\*.*")
      Kill (vars.InsPath & "NTPatcher\5\*.*")
      Kill (vars.InsPath & "NTPatcher\6\*.*")
      Kill (vars.InsPath & "NTPatcher\*.*")
      RmDir vars.InsPath & "NTPatcher\1"
      RmDir vars.InsPath & "NTPatcher\2"
      RmDir vars.InsPath & "NTPatcher\3"
      RmDir vars.InsPath & "NTPatcher\4"
      RmDir vars.InsPath & "NTPatcher\5"
      RmDir vars.InsPath & "NTPatcher\6"
      RmDir vars.InsPath & "NTPatcher"
    End If
    
    'Create directory
    MkDir vars.InsPath & "NTPatcher"
    MkDir vars.InsPath & "NTPatcher\1"
    MkDir vars.InsPath & "NTPatcher\2"
    MkDir vars.InsPath & "NTPatcher\3"
    MkDir vars.InsPath & "NTPatcher\4"
    MkDir vars.InsPath & "NTPatcher\5"
    MkDir vars.InsPath & "NTPatcher\6"
   End If

   'Hide this form
   Me.Enabled = False
   Me.Hide
   Timer2.Enabled = True
  End If
End Sub

Private Sub Timer2_Timer()
  Timer2.Enabled = False
  Screen.MousePointer = vbArrowHourglass
  If (vars.InsType = "1") Then
    Install.Enabled = True
    Install.Show
  ElseIf (vars.InsType = "2") Then
    PyInstall.Enabled = True
    PyInstall.Show
  End If
End Sub
