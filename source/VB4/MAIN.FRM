VERSION 4.00
Begin VB.Form main 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Remeny MultiPatcher"
   ClientHeight    =   6045
   ClientLeft      =   855
   ClientTop       =   3015
   ClientWidth     =   8955
   Enabled         =   0   'False
   Height          =   6555
   Left            =   795
   LinkTopic       =   "main"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "MAIN.frx":0000
   ScaleHeight     =   6045
   ScaleWidth      =   8955
   Top             =   2565
   Visible         =   0   'False
   WhatsThisHelp   =   -1  'True
   Width           =   9075
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   8
      Left            =   5280
      TabIndex        =   22
      Top             =   5040
      Width           =   3495
   End
   Begin VB.CommandButton previousButton 
      Caption         =   "Previous"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6240
      TabIndex        =   21
      Top             =   5640
      Width           =   855
   End
   Begin VB.CommandButton nextButton 
      Caption         =   "Next"
      Height          =   375
      Left            =   7080
      TabIndex        =   20
      Top             =   5640
      Width           =   855
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   7
      Left            =   5280
      TabIndex        =   19
      Top             =   4440
      Width           =   3495
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   6
      Left            =   5280
      TabIndex        =   18
      Top             =   3840
      Width           =   3495
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   5
      Left            =   5280
      TabIndex        =   17
      Top             =   3240
      Width           =   3495
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   4
      Left            =   5280
      TabIndex        =   16
      Top             =   2640
      Width           =   3495
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   3
      Left            =   5280
      TabIndex        =   15
      Top             =   2040
      Width           =   3495
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   2
      Left            =   5280
      TabIndex        =   14
      Top             =   1440
      Width           =   3495
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   1
      Left            =   5280
      TabIndex        =   13
      Top             =   840
      Width           =   3495
   End
   Begin VB.CommandButton backButton 
      Caption         =   "Go up  <---"
      Enabled         =   0   'False
      Height          =   615
      Left            =   4560
      TabIndex        =   8
      Top             =   240
      Visible         =   0   'False
      Width           =   615
   End
   Begin VB.CommandButton itemList 
      Height          =   495
      Index           =   0
      Left            =   5280
      TabIndex        =   4
      Top             =   240
      Width           =   3495
   End
   Begin VB.Timer starttimer 
      Interval        =   1
      Left            =   0
      Top             =   1080
   End
   Begin VB.CommandButton startButton 
      Caption         =   "Start"
      Default         =   -1  'True
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
      Width           =   1095
   End
   Begin VB.CommandButton exitButton 
      Caption         =   "Exit"
      Height          =   375
      Left            =   8040
      TabIndex        =   0
      Top             =   5640
      Width           =   735
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "No items found. Select 'Go Up'"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   495
      Left            =   5280
      TabIndex        =   23
      Top             =   240
      Width           =   3495
   End
   Begin VB.Label execLabel 
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   400
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   495
      Left            =   360
      TabIndex        =   12
      Top             =   4680
      Width           =   4455
   End
   Begin VB.Label dirLabel 
      BackStyle       =   0  'Transparent
      Caption         =   "<update_me>"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   495
      Left            =   1080
      TabIndex        =   11
      Top             =   5160
      Width           =   4095
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "Current Relative Directory:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   615
      Left            =   120
      TabIndex        =   10
      Top             =   5040
      Width           =   855
   End
   Begin VB.Label pageLabel 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "Page <nul>"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   5160
      TabIndex        =   9
      Top             =   5760
      Width           =   975
   End
   Begin VB.Label Version 
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   400
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   495
      Left            =   360
      TabIndex        =   7
      Top             =   2520
      Width           =   4455
   End
   Begin VB.Label Author 
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   400
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   735
      Left            =   360
      TabIndex        =   6
      Top             =   1680
      Width           =   4455
   End
   Begin VB.Label Description 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Select an entry to view its information right here!"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   400
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   1455
      Left            =   360
      TabIndex        =   5
      Top             =   3120
      Width           =   4455
   End
   Begin VB.Label startlabel 
      BackStyle       =   0  'Transparent
      Caption         =   "<-- Click here to begin"
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
      Width           =   3135
   End
   Begin VB.Label OSLabel 
      BackStyle       =   0  'Transparent
      Caption         =   "Windows <unknown>"
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
Attribute VB_Name = "main"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim initDir As String

Dim currentDir As String
Dim FullCurDir As String
Dim menus As New Collection
Dim entries As New Collection
Dim curPage As Integer

Dim EntryExec As String
Dim EntryArgs As String

Sub resetDisplayEntry()
    ' Display defaults
    Author.Caption = ""
    Version.Caption = ""
    Description.Caption = "Select an entry to view its information right here!"
    execLabel.Caption = ""
End Sub

Sub displayEntry(ByVal relativePath As String)
    ' Get info.ini path
    Dim iniPath As String
    iniPath = FullCurPath & "\" & relativePath & "\INFO.INI"
    Debug.Print "ENTRY RELATIVE PATH: " & relativePath
    ' Display information
    Author.Caption = "Author: " & ReadIniStr("MAIN", "Author", iniPath)
    Version.Caption = "Version: " & ReadIniStr("MAIN", "Version", iniPath)
    Description.Caption = "Description: " & ReadIniStr("MAIN", "Description", iniPath)
    execLabel.Caption = "Command: " & ReadIniStr(WinVer, "Exec", iniPath) & " " & ReadIniStr(WinVer, "Args", iniPath)
End Sub


Sub GetItems()
    ' Wait cursor'
    Screen.MousePointer = vbHourglass
    ' Update current directory label
    dirLabel.Caption = currentDir
    ' Update Full path
    FullCurDir = App.Path
    If Right$(FullCurDir, 1) <> "\" Then FullCurDir = FullCurDir & "\"
    FullCurDir = FullCurDir & currentDir
    If Right$(FullCurDir, 1) <> "\" Then FullCurDir = FullCurDir & "\"
    Debug.Print "CURRENT FULLPATH:" & FullCurDir
    Debug.Print "Current RelPath:" & currentDir
    
    ' Scan for items
    Debug.Print "Scanning NOW"
    ' init vars
    Dim item As String, prefix As String
    Set menus = New Collection ' Clear old stuff
    Set entries = New Collection
    ' Directory
    item = Dir$(FullCurDir & "*", vbDirectory)
    Debug.Print "Val of ITEM start: " & item
    ' Get entries and menus
    Do While item <> ""
        Debug.Print "Checking Dir: " & item
        If item <> "." And item <> ".." Then
            prefix = FullCurDir & "\" & item
            Debug.Print prefix
            Debug.Print "ATTR: "; GetAttr(prefix); " NAME: "; item
            If (GetAttr(prefix) And vbDirectory) = vbDirectory Then
                ' This is a valid folder.
                If FileExists(prefix & "\LFN.INI") Then
                    ' Check if this Menu can be added
                    If ReadIniBool("OS", WinVer, prefix & "\LFN.INI", False) Then
                        Debug.Print "GET ITEM: FOUND MENU: " & item
                        menus.Add item
                    End If
                ElseIf FileExists(prefix & "\INFO.INI") Then
                    ' Check if this Menu can be added
                    If ReadIniBool("OS", WinVer, prefix & "\LFN.INI", False) Then
                        Debug.Print "GET ITEM: FOUND ENTRY: " & item
                        entries.Add item
                    End If
                End If
            End If
        End If
        ' Next dir
        item = Dir$
    Loop
    Debug.Print "Val of ITEM end: " & item
    Debug.Print "Count of MENUS " & menus.Count
    Debug.Print "Count of ENTRIES " & entries.Count
    ' Restore cursor
    Screen.MousePointer = vbDefault
End Sub


Sub populateItems(ByVal Page As Integer)
    ' Init vars
    Dim Index As Integer
    Dim itemPos As Integer
    Dim longName As String

    ' Wait cursor
    Screen.MousePointer = vbHourglass

    If Page < 1 Then Page = 1
    curPage = Page

    Debug.Print "TOTAL MENUS: " & menus.Count
    Debug.Print "TOTAL ENTRIES: " & entries.Count

    ' Enable all buttons first
    Dim i As Integer
    For i = 0 To itemList.Count - 1
        itemList(i).Enabled = True
        itemList(i).Caption = ""
        itemList(i).Visible = True
    Next i

    ' Reset entry details
    resetDisplayEntry

    Index = 0
    Do While Index < 9

        ' item index (page taken into account)
        itemPos = (Page - 1) * 9 + (Index + 1)
        Debug.Print "BTN INDEX: "; Index; " ITEM POS: "; itemPos

        ' ---------- MENUS ----------
        If itemPos <= menus.Count Then
            Debug.Print "FOUND MENU: "; menus.item(itemPos)

            longName = ReadIniStr("MAIN", "Name", _
                        FullCurDir & "\" & menus.item(itemPos) & "\LFN.INI")

            If longName = "" Then longName = menus.item(itemPos)

            itemList(Index).Caption = "[MENU] " & longName
            itemList(Index).BackColor = &H8000000F

        ' ---------- ENTRIES ----------
        ElseIf itemPos <= menus.Count + entries.Count Then

            Dim entryPos As Integer
            entryPos = itemPos - menus.Count

            Debug.Print "FOUND ENTRY: "; entries.item(entryPos)

            longName = ReadIniStr("MAIN", "Name", _
                        FullCurDir & "\" & entries.item(entryPos) & "\INFO.INI")

            If longName = "" Then longName = entries.item(entryPos)

            itemList(Index).Caption = longName
            itemList(Index).BackColor = &H4000&

        ' ---------- NO ITEM ----------
        Else
            itemList(Index).Caption = ""
            itemList(Index).Enabled = False
            itemList(Index).Visible = False
        End If

        Index = Index + 1
    Loop

    pageLabel.Caption = "Page " & curPage

    ' Enable/disable NEXT button based on remaining items
    If (menus.Count + entries.Count) > curPage * 9 Then
        nextButton.Enabled = True
    Else
        nextButton.Enabled = False
    End If

    ' Restore cursor
    Screen.MousePointer = vbDefault
End Sub



Private Sub backButton_Click()
    ' Only go up if we are not in init dir
    If Not currentDir = initDir Then
        ' Go up one directory in relative directory
        currentDir = GetParentDir(currentDir)
        ' Call updaters
        GetItems
        populateItems (1)
        ' Disable this button if we are back in init dir
        If currentDir = initDir Then
            backButton.Visible = False
            backButton.Enabled = False
        End If
    End If
End Sub


Private Sub nextButton_Click()
    ' Increase page number
    curPage = curPage + 1
    ' Enable previous button
    previousButton.Enabled = True
    ' Redraw menus and entries
    populateItems (curPage)
End Sub

Private Sub previousButton_click()
    ' Decrease page number
    curPage = curPage - 1
    ' If page is 1 (first page), disable previous button
    If curPage < 2 Then
        previousButton.Enabled = False
    ' Redraw items
    populateItems (curPage)
End Sub


Private Sub exitButton_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    ' Center window
    Me.Left = (Screen.Width - Me.Width) \ 2
    Me.Top = (Screen.Height - Me.Height) \ 2
    ' Get starting directory
    initDir = "RES\"
    currentDir = initDir
    FullCurDir = App.Path + "\RES\"
    ' Play select sound
    Debug.Print "Playing VBSELECT.WAV"
    Dim s$
    s = App.Path & "\DATA\VBSELECT.WAV"
    PlayWavAsync s
    ' Display Windows version
    Debug.Print "OS=" & WinVer
    If WinVer = "nt31" Then
        OSLabel.Caption = "Windows NT 3.1"
    ElseIf WinVer = "nt35" Then
        OSLabel.Caption = "Windows NT 3.5"
    ElseIf WinVer = "nt351" Then
        OSLabel.Caption = "Windows NT 3.51"
    ElseIf WinVer = "nt4" Then
        OSLabel.Caption = "Windows NT 4.0"
    ElseIf WinVer = "w2k" Then
        OSLabel.Caption = "Windows 2000"
    ElseIf WinVer = "wxp" Then
        OSLabel.Caption = "Windows XP"
    ElseIf WinVer = "w31" Then
        OSLabel.Caption = "Windows 3.1"
    ElseIf WinVer = "w95" Then
        OSLabel.Caption = "Windows 95"
    ElseIf WinVer = "w98" Then
        OSLabel.Caption = "Windows 98"
    ElseIf WinVer = "wme" Then
        OSLabel.Caption = "Windows Me"
    End If
    ' Trigger first wave of item population
    GetItems
    populateItems (1)
End Sub



Private Sub itemList_Click(Index As Integer)

    Dim globalPos As Integer
    Dim entryPos As Integer

    ' Reset entry details
    resetDisplayEntry

    ' correct global item position for paged list
    globalPos = (curPage - 1) * 9 + (Index + 1)

    Debug.Print "CLICK BTN:"; Index; " GLOBAL POS:"; globalPos

    ' ---------- MENU ----------
    If globalPos <= menus.Count Then

        Page = 1
        currentDir = currentDir & menus.item(globalPos) & "\"

        GetItems
        populateItems 1

        backButton.Enabled = True
        backButton.Visible = True

    ' ---------- ENTRY ----------
    ElseIf globalPos <= menus.Count + entries.Count Then

        entryPos = globalPos - menus.Count
        Debug.Print "YOU SELECTED ENTRY #" & entryPos

        Dim i As Integer
        For i = 0 To itemList.Count - 1
            itemList(i).Enabled = True
        Next i

        itemList(Index).Enabled = False

        ' PASS CORRECT ENTRY INDEX
        displayEntry entries.item(entryPos)

    End If

End Sub
Private Sub starttimer_Timer()
    If startlabel.Left > 1250 Then
        startlabel.Left = startlabel.Left - 200
    Else
        starttimer.Enabled = False
    End If
End Sub


