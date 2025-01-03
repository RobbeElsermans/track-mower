SamacSys ECAD Model
184102/1505732/2.50/3/3/Integrated Circuit

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r130_60"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.6) (shapeHeight 1.3))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "SOT95P237X112-3N" (originalName "SOT95P237X112-3N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r130_60) (pt -1.05, 0.95) (rotation 90))
			(pad (padNum 2) (padStyleRef r130_60) (pt -1.05, -0.95) (rotation 90))
			(pad (padNum 3) (padStyleRef r130_60) (pt 1.05, 0) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.95 1.77) (pt 1.95 1.77) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.95 1.77) (pt 1.95 -1.77) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.95 -1.77) (pt -1.95 -1.77) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.95 -1.77) (pt -1.95 1.77) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.65 1.46) (pt 0.65 1.46) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.65 1.46) (pt 0.65 -1.46) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.65 -1.46) (pt -0.65 -1.46) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.65 -1.46) (pt -0.65 1.46) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.65 0.51) (pt 0.3 1.46) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.05 1.46) (pt 0.05 1.46) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.05 1.46) (pt 0.05 -1.46) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.05 -1.46) (pt -0.05 -1.46) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.05 -1.46) (pt -0.05 1.46) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.7 1.5) (pt -0.4 1.5) (width 0.2))
		)
	)
	(symbolDef "SI2323DS-T1-E3" (originalName "SI2323DS-T1-E3")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 3) (pt 800 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 570 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -200 mils) (width 6 mils))
		(line (pt 600 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "SI2323DS-T1-E3" (originalName "SI2323DS-T1-E3") (compHeader (numPins 3) (numParts 1) (refDesPrefix IC)
		)
		(compPin "1" (pinName "G") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "S") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "D") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "SI2323DS-T1-E3"))
		(attachedPattern (patternNum 1) (patternName "SOT95P237X112-3N")
			(numPads 3)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
			)
		)
		(attr "Manufacturer_Name" "Vishay")
		(attr "Manufacturer_Part_Number" "SI2323DS-T1-E3")
		(attr "Mouser Part Number" "781-SI2323DS-T1-E3")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Vishay-Semiconductors/SI2323DS-T1-E3?qs=jcx%252B0HVgj2Z84VwYjVEhjA%3D%3D")
		(attr "Arrow Part Number" "SI2323DS-T1-E3")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/si2323ds-t1-e3/vishay?region=europe")
		(attr "Description" "SI2323DS-T1-E3, P-channel MOSFET Transistor 3.7 A 20 V, 3-Pin SOT-23, TO-236")
		(attr "Datasheet Link" "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-DGA23/1580060.pdf")
		(attr "Height" "1.12 mm")
	)

)
