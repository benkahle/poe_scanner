#Postprocessing for PoE Lab 2
require(ggplot2)
require(grid)
require(sphereplot)

#Inport, recenter, and flip scan data
scanData = read.csv("dataIn.csv", header=FALSE)
processingDf = data.frame()
centerX = diff(range(scanData[, 1])) / 2 + min(scanData[, 1])
centerY = diff(range(scanData[, 2])) / 2 + min(scanData[, 2])
processingDf[1:nrow(scanData), "xNorm"] = scanData[, 1] - centerX
processingDf[1:nrow(scanData), "yNorm"] = scanData[, 2] - centerY
processingDf[1:nrow(scanData), "radius"] = scanData[, 3]
processingDf[1:nrow(scanData), "xNorm"] = processingDf[1:nrow(scanData), "xNorm"] * -1
processingDf[1:nrow(scanData), "yNorm"] = processingDf[1:nrow(scanData), "yNorm"] * -1

#Plot scaned data
ggplot(processingDf, aes(x=factor(xNorm), y=factor(yNorm), fill=radius))+
  geom_tile()+
  labs(x="Latitude", y="Longitude", title="Scan of B in Spherical Coordinates")+
  theme(axis.title.x = element_text(size=rel(1)), axis.title.y=element_text(size=rel(1)), title = element_text(size=rel(1.75)), axis.text.x = element_text(size=rel(1),angle=45, vjust=1, hjust=1, colour="Black"), axis.text.y = element_text(size=rel(1), colour="Black"))

#Calibration Fitting Plot
ggplot(newDf, aes(x=data,y=yValue,color=Type))+
  geom_line(size=1.5)+
  labs(x="Distance (cm)",y="Arduino Analog Read Value",title="Calibration Part 1: Fitting")+
  theme(legend.text=element_text(size=rel(1.25)),axis.title.x = element_text(size=rel(1)), axis.title.y = element_text(size=rel(1)), title = element_text(size=rel(1.75)), axis.text.x = element_text(size=rel(1.5)), axis.text.y = element_text(size=rel(1.75)))+
  scale_color_manual(values=c("Black", "Blue", "Green", "Red"))

#Calibration Error Plot
errorDf = read.csv("errorIn.csv", header=FALSE)
colnames(errorDf) = c("dist", "est", "Type")
temp_index = nrow(errorDf)
errorDf[(temp_index+1):(temp_index+2), "dist"] = c(min(errorDf[, "dist"]), max(errorDf[, "dist"]))
errorDf[(temp_index+1):(temp_index+2), "est"] = c(min(errorDf[, "dist"]), max(errorDf[, "dist"]))
errorDf[,"Error"] = abs(errorDf[,"dist"] - errorDf[,"est"])
ggplot(errorDf, aes(x=dist, y=est, colour=Error, shape=Type))+
  geom_point(size=rel(3.5), na.rm=TRUE)+
  labs(x="Actual Distance (cm)", y="Expected Distance (cm)", c)+
  theme(legend.text=element_text(size=rel(1.25)),axis.title.x = element_text(size=rel(1)), axis.title.y = element_text(size=rel(1)), title = element_text(size=rel(1.75)), axis.text.x = element_text(size=rel(1.5)), axis.text.y = element_text(size=rel(1.75)))

#OneD Scan Plot
oneDimDf = read.csv("oneDimScan.csv")
ggplot(oneDimDf, aes(x=lat,y=radius))+
  geom_line(size=1.5)+
  labs(x="Latitude",y="IR Sensor Predicted Range",title="Two Dimensional Scaning")+
  theme(legend.text=element_text(size=rel(1.25)),axis.title.x = element_text(size=rel(1)), axis.title.y = element_text(size=rel(1)), title = element_text(size=rel(1.75)), axis.text.x = element_text(size=rel(1.5)), axis.text.y = element_text(size=rel(1.75)))