object MainForm: TMainForm
  Left = 202
  Top = 103
  Width = 800
  Height = 600
  Caption = 'Transformarea Cosinus Discreta'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 352
    Top = 248
    Width = 105
    Height = 105
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 784
    Height = 561
    ActivePage = TabDetaliu
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabIndex = 1
    TabOrder = 0
    object TabAlegere: TTabSheet
      Caption = 'Alegere imagine'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      object LabelCoordonate: TLabel
        Left = 576
        Top = 492
        Width = 88
        Height = 13
        Caption = 'Coordonate punct:'
      end
      object LabelDimensiuni: TLabel
        Left = 148
        Top = 492
        Width = 3
        Height = 13
      end
      object ScrollBoxImagine: TScrollBox
        Left = 8
        Top = 8
        Width = 753
        Height = 473
        TabOrder = 0
        object Imagine: TImage
          Left = 0
          Top = 0
          Width = 749
          Height = 469
          AutoSize = True
          OnClick = ImagineClick
          OnMouseMove = ImagineMouseMove
        end
        object ShapeDetaliu: TShape
          Left = 0
          Top = 0
          Width = 8
          Height = 8
          Pen.Color = clRed
          Pen.Mode = pmMask
          Pen.Style = psInsideFrame
          Pen.Width = 2
          Visible = False
          OnMouseDown = ShapeDetaliuMouseDown
        end
      end
      object EditX: TEdit
        Left = 672
        Top = 488
        Width = 41
        Height = 21
        ReadOnly = True
        TabOrder = 1
      end
      object EditY: TEdit
        Left = 718
        Top = 488
        Width = 41
        Height = 21
        ReadOnly = True
        TabOrder = 2
      end
      object ButtonIncarca: TButton
        Left = 16
        Top = 488
        Width = 89
        Height = 25
        Caption = '&Incarca imagine'
        TabOrder = 3
        OnClick = ButtonIncarcaClick
      end
    end
    object TabDetaliu: TTabSheet
      Caption = 'Detaliu imagine'
      ImageIndex = 1
      object ImagineDetalii: TImage
        Left = 6
        Top = 48
        Width = 384
        Height = 384
        OnMouseMove = ImagineDetaliiMouseMove
      end
      object LabelEgalTab2: TLabel
        Left = 392
        Top = 192
        Width = 46
        Height = 92
        Caption = '='
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -85
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object StringGridS: TStringGrid
        Left = 440
        Top = 48
        Width = 327
        Height = 385
        BorderStyle = bsNone
        ColCount = 8
        DefaultColWidth = 40
        DefaultRowHeight = 47
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ScrollBars = ssNone
        TabOrder = 0
        OnDrawCell = StringGridSDrawCell
      end
      object ButtonTranslare: TButton
        Left = 336
        Top = 488
        Width = 89
        Height = 25
        Caption = '&Translare'
        TabOrder = 1
        OnClick = ButtonTranslareClick
      end
    end
    object TabTranslare: TTabSheet
      Caption = 'Translare matrice'
      ImageIndex = 2
      object LabelT3b: TLabel
        Left = 384
        Top = 224
        Width = 28
        Height = 64
        Caption = '='
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -53
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object LabelT3a: TLabel
        Left = 378
        Top = 216
        Width = 6
        Height = 32
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -29
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 376
        Top = 216
        Width = 44
        Height = 13
        Caption = 'Translare'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = 12
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object StringGridT2: TStringGrid
        Left = 440
        Top = 48
        Width = 327
        Height = 385
        BorderStyle = bsNone
        ColCount = 8
        DefaultColWidth = 40
        DefaultRowHeight = 47
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ScrollBars = ssNone
        TabOrder = 0
        OnDrawCell = StringGridT2DrawCell
      end
      object StringGridT1: TStringGrid
        Left = 40
        Top = 48
        Width = 327
        Height = 385
        BorderStyle = bsNone
        ColCount = 8
        DefaultColWidth = 40
        DefaultRowHeight = 47
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ScrollBars = ssNone
        TabOrder = 1
        OnDrawCell = StringGridT1DrawCell
        OnSelectCell = StringGridT1SelectCell
      end
      object ButtonDCT: TButton
        Left = 336
        Top = 488
        Width = 97
        Height = 25
        Caption = '&Transformare DCT'
        TabOrder = 2
        OnClick = ButtonDCTClick
      end
    end
    object TabDCT: TTabSheet
      Caption = 'DCT'
      ImageIndex = 3
      object LabelT4b: TLabel
        Left = 392
        Top = 240
        Width = 28
        Height = 64
        Caption = '='
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -53
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object LabelT4a: TLabel
        Left = 378
        Top = 216
        Width = 56
        Height = 32
        Caption = 'DCT'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -29
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object StringGridD1: TStringGrid
        Left = 40
        Top = 48
        Width = 327
        Height = 385
        BorderStyle = bsNone
        ColCount = 8
        DefaultColWidth = 40
        DefaultRowHeight = 47
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ScrollBars = ssNone
        TabOrder = 0
        OnDrawCell = StringGridD1DrawCell
        OnSelectCell = StringGridD1SelectCell
      end
      object StringGridD2: TStringGrid
        Left = 440
        Top = 48
        Width = 327
        Height = 385
        BorderStyle = bsNone
        ColCount = 8
        DefaultColWidth = 40
        DefaultRowHeight = 47
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ScrollBars = ssNone
        TabOrder = 1
        OnDrawCell = StringGridD2DrawCell
      end
    end
  end
  object OpenDialogImagine: TOpenDialog
    Left = 360
  end
end
