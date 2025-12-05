Attribute VB_Name = "FUNCTION"
Declare Function mciSendString Lib "MMSYSTEM.DLL" _
    (ByVal lpstrCommand As String, ByVal lpstrReturnString _
    As String, ByVal uReturnLength As Integer, ByVal hwndCallback _
    As Integer) As Integer

Declare Function GetPrivateProfileString Lib "KERNEL" _
    (ByVal lpApplicationName As String, ByVal lpKeyName As String, _
     ByVal lpDefault As String, ByVal lpReturnedString As String, _
     ByVal nSize As Integer, ByVal lpFileName As String) As Integer

Declare Function GetPrivateProfileInt Lib "KERNEL" _
    (ByVal lpApplicationName As String, ByVal lpKeyName As String, _
     ByVal nDefault As Integer, ByVal lpFileName As String) As Integer

Public WinVer As String

Function InCollection(c As Collection, k As String) As Boolean
    On Error Resume Next
    Dim v
    v = c.item(k)
    InCollection = (Err.Number = 0)
    Err.Clear
End Function

Function GetParentDir(ByVal p As String) As String
    Dim i As Integer

    ' remove trailing backslash first
    If Right$(p, 1) = "\" Then
        p = Left$(p, Len(p) - 1)
    End If

    ' search backward for last backslash
    For i = Len(p) To 1 Step -1
        If Mid$(p, i, 1) = "\" Then
            GetParentDir = Left$(p, i)
            Exit Function
        End If
    Next i

    ' no backslash found
    GetParentDir = ""
End Function

Function FileExists(ByVal fname As String) As Boolean
    On Error Resume Next
    Dim a As Long
    a = GetAttr(fname)
    FileExists = (Err.Number = 0)
    Err.Clear
End Function

Function ReadIniStr(section As String, key As String, file As String) As String
    Dim buffer As String * 256
    Dim length As Integer

    Debug.Print "Reading " & file & " Sect " & section & " Key " & key
    length = GetPrivateProfileString(section, key, "", buffer, Len(buffer), file)
    ReadIniStr = Left$(buffer, length)
End Function

Function ReadIniBool(section As String, key As String, file As String, defaultValue As Boolean) As Boolean
    Dim s As String
    s = LCase$(Trim$(ReadIniStr(section, key, file)))

    If s = "" Then
        ReadIniBool = defaultValue
    ElseIf s = "1" Or s = "true" Or s = "yes" Or s = "on" Then
        ReadIniBool = True
    Else
        ReadIniBool = False
    End If
End Function

Function ReadIniInt(section As String, key As String, file As String) As Integer
    ReadIniInt = GetPrivateProfileInt(section, key, 0, file)
End Function

'
Sub PlayWavAsync(filename$)
    mciSendString "open """ & filename$ & """ type waveaudio alias snd", 0, 0, 0
    mciSendString "play snd from 0", 0, 0, 0   ' async by default in Win16
End Sub














Sub StopWav()
    mciSendString "stop snd", 0, 0, 0
    mciSendString "close snd", 0, 0, 0
End Sub

