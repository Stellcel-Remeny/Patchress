VERSION 5.00
Begin VB.MDIForm BkgdWindow 
   Appearance      =   0  'Flat
   BackColor       =   &H00808000&
   Caption         =   "NTPatcher 5.0 Public"
   ClientHeight    =   6225
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11205
   Icon            =   "MDIForm1.frx":0000
   LinkTopic       =   "MDIForm1"
   Moveable        =   0   'False
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
End
Attribute VB_Name = "BkgdWindow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
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

    ' Get the handle of the taskbar
    hTaskbar = FindWindow("Shell_TrayWnd", vbNullString)

    ' Get the taskbar dimensions
    GetWindowRect hTaskbar, rect

    ' Calculate the taskbar height
    TaskbarHeight = rect.Bottom - rect.Top
End Function

Private Sub MDIForm_Load()
    Me.Top = 0
    Me.Left = 0
    Me.Width = Screen.Width
    Me.Height = Screen.Height - TaskbarHeight()
End Sub

Private Sub MDIForm_Resize()
    If Me.WindowState <> vbMaximized And Me.WindowState <> vbMinimized Then
        Me.WindowState = vbMaximized
    End If
End Sub
