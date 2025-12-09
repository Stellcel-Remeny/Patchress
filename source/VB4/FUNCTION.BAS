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
    Dim f As Integer
    Dim line As String
    Dim curSection As String
    Dim p As Integer
    Dim value As String

    On Error GoTo Fail
    f = FreeFile
    Open file For Input As #f

    Do Until EOF(f)
        Line Input #f, line
        line = Trim$(line)

        If Len(line) = 0 Then GoTo NextLine
        If Left$(line, 1) = ";" Then GoTo NextLine

        ' Section header
        If Left$(line, 1) = "[" And Right$(line, 1) = "]" Then
            curSection = Mid$(line, 2, Len(line) - 2)
            GoTo NextLine
        End If

        ' Key match
        If LCase$(curSection) = LCase$(section) Then
            p = InStr(line, "=")
            If p > 0 Then
                If LCase$(Left$(line, p - 1)) = LCase$(key) Then
                    value = Trim$(Mid$(line, p + 1))

                    ' Strip one pair of surrounding quotes, if there is.
                    If Len(value) >= 2 Then
                        If (Left$(value, 1) = """" And Right$(value, 1) = """") _
                        Or (Left$(value, 1) = "'" And Right$(value, 1) = "'") Then
                            value = Mid$(value, 2, Len(value) - 2)
                        End If
                    End If

                    ReadIniStr = value
                    Close #f
                    Exit Function
                End If
            End If
        End If

NextLine:
    Loop

Fail:
    On Error Resume Next
    If f <> 0 Then Close #f
    ReadIniStr = ""
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

Sub PlayWavAsync(filename$)
    ' by chatgpt vibe code
    ' and sound STILL does not work in win9x bruh
    Dim cmd As String

    ' Always close previous alias (Win95 requires this)
    mciSendString "close snd", 0, 0, 0

    ' ---- Windows 3.1 ONLY ----
    If InStr(1, WinVer, "3", vbTextCompare) > 0 Then
        ' Win3.1: NO quotes, MUST use WAVE
        cmd = "open " & filename$ & " type WAVE alias snd"

    ' ---- Windows 95 / 98 / ME ----
    ElseIf InStr(1, WinVer, "95", vbTextCompare) > 0 _
       Or InStr(1, WinVer, "98", vbTextCompare) > 0 _
       Or InStr(1, WinVer, "ME", vbTextCompare) > 0 Then

        ' Win95 family: NO quotes, BUT MUST use waveaudio
        cmd = "open " & filename$ & " type waveaudio alias snd"

    ' ---- Windows NT / 2000 / XP ----
    Else
        ' NT family: quotes + waveaudio
        cmd = "open """ & filename$ & """ type waveaudio alias snd"
    End If

    ' Open + async play
    mciSendString cmd, 0, 0, 0
    mciSendString "play snd", 0, 0, 0
End Sub
















