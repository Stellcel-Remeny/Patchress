VERSION 5.00
Begin VB.Form PyInstall 
   BackColor       =   &H00404040&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Installing NTPatcher"
   ClientHeight    =   1965
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4815
   ControlBox      =   0   'False
   Icon            =   "PyInstall.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   1965
   ScaleWidth      =   4815
   ShowInTaskbar   =   0   'False
   Begin VB.Timer Timer2 
      Interval        =   2000
      Left            =   360
      Top             =   0
   End
   Begin VB.Timer Timer1 
      Interval        =   300
      Left            =   0
      Top             =   0
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Patching NTLDR..."
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
      Left            =   1320
      TabIndex        =   1
      Top             =   720
      Visible         =   0   'False
      Width           =   2175
   End
   Begin VB.Label Label3 
      BackStyle       =   0  'Transparent
      Caption         =   "Creating Backup..."
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
      Left            =   1320
      TabIndex        =   0
      Top             =   720
      Width           =   2175
   End
End
Attribute VB_Name = "PyInstall"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
 
Private Declare Function OpenProcess Lib "kernel32" ( _
    ByVal dwDesiredAccess As Long, ByVal bInheritHandle As Long, ByVal dwProcessId As Long) As Long
    
Private Declare Function CloseHandle Lib "kernel32" ( _
    ByVal hObject As Long) As Long
 
Private Declare Function EnumProcesses Lib "PSAPI.DLL" ( _
   lpidProcess As Long, ByVal cb As Long, cbNeeded As Long) As Long
 
Private Declare Function EnumProcessModules Lib "PSAPI.DLL" ( _
    ByVal hProcess As Long, lphModule As Long, ByVal cb As Long, lpcbNeeded As Long) As Long
 
Private Declare Function GetModuleBaseName Lib "PSAPI.DLL" Alias "GetModuleBaseNameA" ( _
    ByVal hProcess As Long, ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Long
 
Private Const PROCESS_VM_READ = &H10
Private Const PROCESS_QUERY_INFORMATION = &H400
 
Private Function IsProcessRunning(ByVal sProcess As String) As Boolean
    Const MAX_PATH As Long = 260
    Dim lProcesses() As Long, lModules() As Long, N As Long, lRet As Long, hProcess As Long
    Dim sName As String
    
    sProcess = UCase$(sProcess)
    
    ReDim lProcesses(1023) As Long
    If EnumProcesses(lProcesses(0), 1024 * 4, lRet) Then
        For N = 0 To (lRet \ 4) - 1
            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION Or PROCESS_VM_READ, 0, lProcesses(N))
            If hProcess Then
                ReDim lModules(1023)
                If EnumProcessModules(hProcess, lModules(0), 1024 * 4, lRet) Then
                    sName = String$(MAX_PATH, vbNullChar)
                    GetModuleBaseName hProcess, lModules(0), sName, MAX_PATH
                    sName = Left$(sName, InStr(sName, vbNullChar) - 1)
                    If Len(sName) = Len(sProcess) Then
                        If sProcess = UCase$(sName) Then IsProcessRunning = True: Exit Function
                    End If
                End If
            End If
            CloseHandle hProcess
        Next N
    End If
End Function
 

Private Sub Form_Load()
  Me.BackColor = RGB(28, 78, 153)
  Me.Left = (BkgdWindow.Width - Me.Width) / 1.014
  Me.Top = (BkgdWindow.Height - Me.Height) / 1.1
End Sub

Private Sub Timer1_Timer()
  Timer1.Enabled = False
  SetAttr vars.InsPath & "ntldr", vbNormal
  Shell "CMD.EXE /c ""copy " & vars.InsPath & "ntldr " & vars.InsPath & "ntldr.bak""", vbHide
  Label3.Visible = False
  Label1.Visible = True
  Shell ".\hexbyte2.exe", vbHide
  Timer2.Enabled = True
End Sub

Private Sub Timer2_Timer()
  Timer2.Enabled = False
  If (IsProcessRunning("hexbyte2.exe") = False) Then
    vars.Qexit = "1"
  End If
  If (vars.Qexit <> "1") Then
    Timer2.Enabled = True
  Else
    Me.Enabled = False
    Me.Hide
    Shell "cmd.exe /c ""attrib +s +h +r " & vars.InsPath & "ntldr >nul""", vbHide
    InsFinish.Enabled = True
    InsFinish.Left = PInstall.Left
    InsFinish.Top = PInstall.Top
    InsFinish.Show
  End If
End Sub
