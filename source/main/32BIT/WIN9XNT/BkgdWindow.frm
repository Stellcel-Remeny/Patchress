VERSION 5.00
Begin VB.MDIForm BkgdWindow 
   Appearance      =   0  'Flat
   BackColor       =   &H00808000&
   Caption         =   "NTPatcher 6.1 Public"
   ClientHeight    =   6225
   ClientLeft      =   165
   ClientTop       =   555
   ClientWidth     =   9120
   Enabled         =   0   'False
   Icon            =   "BkgdWindow.frx":0000
   LinkTopic       =   "MDIForm1"
   Moveable        =   0   'False
   ScrollBars      =   0   'False
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
End
Attribute VB_Name = "BkgdWindow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim result As VbMsgBoxResult
Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function GetWindowRect Lib "user32" (ByVal hwnd As Long, lpRect As rect) As Long
Private Const WM_NCLBUTTONDBLCLK As Long = &HA3

Private Type rect
    Left As Long
    Top As Long
    Right As Long
    Bottom As Long
End Type

Private Function TaskbarHeight() As Integer
    Dim rect As rect
    Dim hTaskbar As Long
    hTaskbar = FindWindow("Shell_TrayWnd", vbNullString)
    GetWindowRect hTaskbar, rect
    TaskbarHeight = rect.Bottom - rect.Top
End Function

Private Sub MDIForm_Load()
  Me.Top = 0
  Me.Left = 0
  Me.Width = Screen.Width
  Me.Height = Screen.Height - TaskbarHeight()
  Me.BackColor = RGB(0, 51, 153)
  BkgdText.BackColor = RGB(0, 51, 153)
  BkgdText.Show
  WelcomeWindow.Enabled = True
  WelcomeWindow.Show
  FSplash2.Enabled = True
  FSplash2.Show
End Sub

Private Sub MDIForm_Resize()
  If Me.WindowState <> vbMaximized And Me.WindowState <> vbMinimized Then
      Me.WindowState = vbMaximized
  End If
End Sub

Private Sub MDIForm_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  Cancel = 1
  If (vars.NTerm = "1") Then End
  If Not (vars.AlrExit = "1") Then
    result = MsgBox("If you exit now, your changes will be discarded. Are you sure that you want to exit NTPatcher?", vbQuestion + vbYesNo, "Exit NTPatcher - Confirmation")
    If result = vbYes Then
      End
    Else
    End If
  End If
End Sub
