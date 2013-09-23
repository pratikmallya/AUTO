      IMPLICIT NONE
      INTEGER MXLLN,MXNLB,MXLLB,i,lnl,lbl,length
      PARAMETER (MXLLN=120,MXNLB=18,MXLLB=20)
      CHARACTER*120 line
      CHARACTER*20 label(MXNLB)
      DATA label/'first','second','third','fourth','fifth','sixth',
     *           'seventh','eighth','ninth','tenth','eleventh',
     *           'twelfth','thirtheenth','fourteenth','fifteenth',
     *            'sixteenth','seventeenth','eightteenth'/
C
 1    READ(1,101,END=99)line
        lnl=length(line)
        DO i=1,MXNLB
          lbl=length(label(i))
          IF(line(1:lbl).EQ.label(i)(1:lbl))THEN
            line(lbl+1:lbl+8)=':	$(EXE)'
            lnl=lnl+7
          ENDIF         
        ENDDO
        WRITE(2,102)(line(i:i),i=1,lnl)
      GOTO 1
C
 101  FORMAT((A))
 102  FORMAT(120A1)
 99   STOP
      END
C
      INTEGER FUNCTION length(str)
      IMPLICIT NONE
      CHARACTER*(*) str
      INTEGER i
C
      length=0
      DO i=LEN(str),1,-1
        length=i
        IF(str(i:i).NE.' ')RETURN
      ENDDO
C
      RETURN
      END
