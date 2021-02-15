function [u] = V2X_DENM_expander(y, z)
%#eml
  u = z;
  u = FILTER_PRESCAN_V2X_FIXED_DENM_MESSAGE(u, y);
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_MESSAGE(u, y)
  u.HEADER = FILTER_PRESCAN_HEADER(u.HEADER, y.HEADER);
  u.DATA = FILTER_PRESCAN_V2X_FIXED_DENM_DATA(u.DATA, y.DATA);
end

function [u] = FILTER_PRESCAN_HEADER(u, y)
  u.valid = y.valid;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_DATA(u, y)
  u.header = FILTER_PRESCAN_V2X_FIXED_DENM_header(u.header, y.header);
  u.denm = FILTER_PRESCAN_V2X_FIXED_DENM_denm(u.denm, y.denm);
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_header(u, y)
  u.protocolVersion = y.protocolVersion;
  u.messageID = y.messageID;
  u.stationID = y.stationID;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_denm(u, y)
  u.management = FILTER_PRESCAN_V2X_FIXED_DENM_management(u.management, y.management);
  u.situation = FILTER_PRESCAN_V2X_FIXED_DENM_situation(u.situation, y.situation);
  u.alacarte = FILTER_PRESCAN_V2X_FIXED_DENM_alacarte(u.alacarte, y.alacarte);
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_management(u, y)
  u.actionID = FILTER_PRESCAN_V2X_FIXED_DENM_actionID(u.actionID, y.actionID);
  u.detectionTime = y.detectionTime;
  u.referenceTime = y.referenceTime;
  u.eventPosition = FILTER_PRESCAN_V2X_FIXED_DENM_eventPosition(u.eventPosition, y.eventPosition);
  u.relevanceDistance = y.relevanceDistance;
  u.relevanceTrafficDirection = y.relevanceTrafficDirection;
  u.validityDuration = y.validityDuration;
  u.stationType = y.stationType;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_actionID(u, y)
  u.originatingStationID = y.originatingStationID;
  u.sequenceNumber = y.sequenceNumber;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_eventPosition(u, y)
  u.latitude = y.latitude;
  u.longitude = y.longitude;
  u.positionConfidenceEllipse = FILTER_PRESCAN_V2X_FIXED_DENM_positionConfidenceEllipse(u.positionConfidenceEllipse, y.positionConfidenceEllipse);
  u.altitude = FILTER_PRESCAN_V2X_FIXED_DENM_altitude(u.altitude, y.altitude);
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_positionConfidenceEllipse(u, y)
  u.semiMajorConfidence = y.semiMajorConfidence;
  u.semiMinorConfidence = y.semiMinorConfidence;
  u.semiMajorOrientation = y.semiMajorOrientation;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_altitude(u, y)
  u.altitudeValue = y.altitudeValue;
  u.altitudeConfidence = y.altitudeConfidence;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_situation(u, y)
  u.informationQuality = y.informationQuality;
  u.eventType = FILTER_PRESCAN_V2X_FIXED_DENM_eventType(u.eventType, y.eventType);
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_eventType(u, y)
  u.causeCode = y.causeCode;
  u.subCauseCode = y.subCauseCode;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_alacarte(u, y)
  u.roadWorks = FILTER_PRESCAN_V2X_FIXED_DENM_roadWorks(u.roadWorks, y.roadWorks);
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_roadWorks(u, y)
  u.closedLanes = FILTER_PRESCAN_V2X_FIXED_DENM_closedLanes(u.closedLanes, y.closedLanes);
  u.speedLimit = y.speedLimit;
end

function [u] = FILTER_PRESCAN_V2X_FIXED_DENM_closedLanes(u, y)
  u.drivingLaneStatus = y.drivingLaneStatus;
end

