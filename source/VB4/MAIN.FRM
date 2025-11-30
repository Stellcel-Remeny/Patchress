VERSION 4.00
Begin VB.Form main 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Welcome to MultiPatcher"
   ClientHeight    =   6075
   ClientLeft      =   5970
   ClientTop       =   2565
   ClientWidth     =   8955
   Height          =   6585
   Left            =   5910
   LinkTopic       =   "main"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "MAIN.frx":0000
   ScaleHeight     =   6075
   ScaleWidth      =   8955
   Top             =   2115
   WhatsThisHelp   =   -1  'True
   Width           =   9075
   Begin VB.CommandButton Command3 
      Caption         =   "<-- Previous"
      Height          =   375
      Left            =   5160
      TabIndex        =   2
      Top             =   5640
      Width           =   1095
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Exit"
      Height          =   375
      Left            =   7440
      TabIndex        =   1
      Top             =   5640
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Next -->"
      Height          =   375
      Left            =   6240
      TabIndex        =   0
      Top             =   5640
      Width           =   1095
   End
   Begin VB.Label OSLabel 
      BackStyle       =   0  'Transparent
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   855
      Left            =   1440
      TabIndex        =   3
      Top             =   1320
      Width           =   3495
   End
End
Attribute VB_Name = "main"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Private Sub Text1_Change()

End Sub


