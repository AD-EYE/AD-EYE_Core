function listOfNames = OpenScenarioMod(fileName)
%go to correct folder
cd '..\OpenSCENARIO_experiments'

fileID = fopen([fileName, '.xosc']);
document = fscanf(fileID, '%c');
fclose(fileID);

%search for the array, array of form [x,y,z]
findOpen = strfind(document, '[');
findClose = strfind(document, ']');
findSeparator = strfind(document, ',');

for c = 1:length(findOpen)
    changes(c).textOrigin = findOpen(c);
    changes(c).textBrake1 = findSeparator(2*c-1);
    changes(c).textBrake2 = findSeparator(2*c);
    changes(c).textEnd = findClose(c);
    changes(c).valueLow = str2double(extractBetween(document, changes(c).textOrigin+1, changes(c).textBrake1-1));
    changes(c).valueStep = str2double(extractBetween(document, changes(c).textBrake1+1, changes(c).textBrake2-1));
    changes(c).valueHigh = str2double(extractBetween(document, changes(c).textBrake2+1, changes(c).textEnd-1));
end

%copy document
documentList(1,1)={document};

%change document
for c = 1:length(changes)
    colum = 1;
    for p = 1:size(documentList,2)
        for v = changes(c).valueLow:changes(c).valueStep:changes(c).valueHigh
            documentList(c+1,colum) = replaceBetween(documentList(c,p),changes(c).textOrigin, changes(c).textEnd, sprintf('%.6f', v));
            colum = colum+1;
        end
    end
end

lastRow = size(documentList,1);
%output
for colum = 1:size(documentList,2)
    fileID = fopen([fileName, sprintf('%.0f', colum), '.xosc'],'w');
    listOfNames(colum) = convertCharsToStrings([fileName, sprintf('%.0f', colum), '.xosc']);
    doc = documentList(lastRow, colum);
    fwrite(fileID,doc{1});
    fclose(fileID);
end

%back to code
cd '..\Code'
end

