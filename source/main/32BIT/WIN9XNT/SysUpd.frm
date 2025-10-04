VERSION 5.00
Begin VB.Form SysUpd 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   0  'None
   ClientHeight    =   1335
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6735
   Icon            =   "SysUpd.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   1335
   ScaleWidth      =   6735
   ShowInTaskbar   =   0   'False
   Begin VB.Timer Timer5 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   6240
      Top             =   840
   End
   Begin VB.Timer Timer4 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   6240
      Top             =   480
   End
   Begin VB.PictureBox Picture2 
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   735
      Left            =   720
      Picture         =   "SysUpd.frx":030A
      ScaleHeight     =   735
      ScaleWidth      =   735
      TabIndex        =   2
      Top             =   240
      Visible         =   0   'False
      Width           =   735
   End
   Begin VB.Timer Timer3 
      Interval        =   1000
      Left            =   6240
      Top             =   120
   End
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   25
      Left            =   480
      Top             =   120
   End
   Begin VB.Timer Timer1 
      Interval        =   25
      Left            =   120
      Top             =   120
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   840
      Picture         =   "SysUpd.frx":5AEC
      ScaleHeight     =   615
      ScaleWidth      =   615
      TabIndex        =   0
      Top             =   360
      Width           =   615
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00808080&
      BorderWidth     =   5
      X1              =   0
      X2              =   6840
      Y1              =   1320
      Y2              =   1320
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Setup is updating System files..."
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   1560
      TabIndex        =   1
      Top             =   480
      Width           =   5055
   End
   Begin VB.Line Line4 
      BorderColor     =   &H00E0E0E0&
      BorderWidth     =   5
      X1              =   0
      X2              =   0
      Y1              =   1320
      Y2              =   0
   End
   Begin VB.Line Line3 
      BorderColor     =   &H00E0E0E0&
      BorderWidth     =   5
      X1              =   0
      X2              =   6840
      Y1              =   0
      Y2              =   0
   End
   Begin VB.Line Line2 
      BorderColor     =   &H00808080&
      BorderWidth     =   5
      X1              =   6720
      X2              =   6720
      Y1              =   1320
      Y2              =   0
   End
End
Attribute VB_Name = "SysUpd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim WshShell As Object
  
Private Sub Form_Load()
  Me.Left = (BkgdWindow.Width - Me.Width) / 2
  Me.Top = (BkgdWindow.Height - Me.Height) / 2
End Sub

Private Sub Timer1_Timer()
  Timer1.Enabled = False
  Screen.MousePointer = vbNormal
  Timer2.Enabled = True
End Sub

Private Sub Timer2_Timer()
  Timer2.Enabled = False
  Screen.MousePointer = vbHourglass
  Timer1.Enabled = True
End Sub

Private Sub Timer3_Timer()
  Timer3.Enabled = False

  SetAttr vars.InsPath & "BOOT.INI", vbNormal
  AddLine = vars.InsPath & "BXTC1.DAT"
  AddLine = AddLine & "="" "" "
  Open vars.InsPath & "BOOT.INI" For Append As #1
    Print #1, AddLine
    AddLine = vars.InsPath & "BXTC2.DAT"
    AddLine = AddLine & "="" "" "
    Print #1, AddLine
    AddLine = vars.InsPath & "BXTC3.DAT"
    AddLine = AddLine & "="" "" "
    Print #1, AddLine
    AddLine = vars.InsPath & "BXTC4.DAT"
    AddLine = AddLine & "="" "" "
    Print #1, AddLine
    AddLine = vars.InsPath & "BXTC5.DAT"
    AddLine = AddLine & "="" "" "
    Print #1, AddLine
    AddLine = vars.InsPath & "BXTC6.DAT"
    AddLine = AddLine & "="" "" "
    Print #1, AddLine
    AddLine = vars.InsPath & "BXTC7.DAT"
    AddLine = AddLine & "="" "" "
    Print #1, AddLine
    AddLine = vars.InsPath & "BXTC8.DAT"
    AddLine = AddLine & "="" "" "
    Print #1, AddLine
  Close #1
  
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BOOT.INI >nul""", vbHide
  
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN1 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN2 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN3 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN4 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN5 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN6 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN7 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "PTCN8 >nul""", vbHide
  
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC1.DAT >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC2.DAT >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC3.DAT >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC4.DAT >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC5.DAT >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC6.DAT >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC7.DAT >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "BXTC8.DAT >nul""", vbHide
  
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n01 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n02 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n03 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n04 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n05 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n06 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n07 >nul""", vbHide
  Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "mtmp.n08 >nul""", vbHide
  
  Timer1.Enabled = False
  Timer2.Enabled = False
  Screen.MousePointer = vbHourglass
  Label1.Caption = "Setup is updating the registry..."
  Picture1.Visible = False
  Picture2.Visible = True
  Timer4.Enabled = True
End Sub

Private Sub Timer4_Timer()
  Timer4.Enabled = False
  'Settings
  SaveSetting "NTPatcher Toolkit", "Settings", "InsLetter", vars.InsPath
  'ShowToken
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit1", "1"
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit2", "1"
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit3", "1"
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit4", "1"
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit5", "1"
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit6", "1"
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit7", "1"
  SaveSetting "NTPatcher Toolkit", "ShowToken", "unit8", "1"
  'Use
  SaveSetting "NTPatcher Toolkit", "Use", "unit1", "5"
  SaveSetting "NTPatcher Toolkit", "Use", "unit2", "5"
  SaveSetting "NTPatcher Toolkit", "Use", "unit3", "5"
  SaveSetting "NTPatcher Toolkit", "Use", "unit4", "5"
  SaveSetting "NTPatcher Toolkit", "Use", "unit5", "5"
  SaveSetting "NTPatcher Toolkit", "Use", "unit6", "5"
  SaveSetting "NTPatcher Toolkit", "Use", "unit7", "5"
  SaveSetting "NTPatcher Toolkit", "Use", "unit8", "5"
  'Strings
  SaveSetting "NTPatcher Toolkit", "Strings", "unit1", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  SaveSetting "NTPatcher Toolkit", "Strings", "unit2", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  SaveSetting "NTPatcher Toolkit", "Strings", "unit3", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  SaveSetting "NTPatcher Toolkit", "Strings", "unit4", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  SaveSetting "NTPatcher Toolkit", "Strings", "unit5", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  SaveSetting "NTPatcher Toolkit", "Strings", "unit6", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  SaveSetting "NTPatcher Toolkit", "Strings", "unit7", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  SaveSetting "NTPatcher Toolkit", "Strings", "unit8", "multi(0)disk(0)rdisk(0)partition(0)\="" "" "
  'Shortcuts (if enabled) - Desktop
  Set WshShell = CreateObject("WScript.Shell")
  If (vars.CDeskIcon = "1") Then
    With WshShell.CreateShortcut(WshShell.SpecialFolders("Desktop") & "\NTPatcher Toolkit.lnk")
        .TargetPath = vars.InsPath & "NTPatcher\Toolkit.exe"
        .WorkingDirectory = vars.InsPath & "NTPatcher"
        .IconLocation = vars.InsPath & "NTPatcher\Toolkit.exe,0"
        .Description = "Edits the boot entries created by NTPatcher."
        .Save
    End With
  End If
  If (vars.CStartIcon = "1") Then
    With WshShell.CreateShortcut(WshShell.SpecialFolders("AllUsersPrograms") & "\NTPatcher Toolkit.lnk")
        .TargetPath = vars.InsPath & "NTPatcher\Toolkit.exe"
        .WorkingDirectory = vars.InsPath & "NTPatcher"
        .IconLocation = vars.InsPath & "NTPatcher\Toolkit.exe,0"
        .Description = "Edits the boot entries created by NTPatcher."
        .Save
    End With
  End If
  Set WshShell = Nothing
  'Hide form
  Me.Enabled = False
  Me.Hide
  Timer5.Enabled = True
End Sub

Private Sub Timer5_Timer()
  Timer5.Enabled = False
  Screen.MousePointer = vbNormal
  InsFinish.Top = Prepare.Top
  InsFinish.Left = Prepare.Left
  InsFinish.Enabled = True
  InsFinish.Show
End Sub
