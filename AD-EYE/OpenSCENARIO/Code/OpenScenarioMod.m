function listOfNames = openscenariomod(file_name)
%go to correct folder
cd '..\OpenSCENARIO_experiments'

fileID = fopen([file_name, '.xosc']);
document = fscanf(fileID, '%c');
fclose(fileID);

%search for the array, array of form [x,y,z]
findOpen = strfind(document, '[');
findClose = strfind(document, ']');
%findSeparator = strfind(document, ',');

if isempty(findOpen)
    listOfNames(1) = convertCharsToStrings([file_name, '.xosc']);
    cd '..\Code';
    return
end


for c = 1:length(findOpen)
    changes(c).textOrigin = findOpen(c);
    changes(c).textEnd = findClose(c);
    text = extractBetween(document,  findOpen(c)+1,  findClose(c)-1)
    findSeparator = strfind(text, ',');
    findSeparator = findSeparator{1,1};
    changes(c).valueLow = str2double(extractBetween(document, changes(c).textOrigin+1, changes(c).textOrigin-1+findSeparator(1)));
    changes(c).valueStep = str2double(extractBetween(document, changes(c).textOrigin+1+findSeparator(1), changes(c).textOrigin-1+findSeparator(2)));
    changes(c).valueHigh = str2double(extractBetween(document, changes(c).textOrigin+1+findSeparator(2), changes(c).textEnd-1));
end

%copy the document
documentList(1,1)={document};

%modify the document
for c = 1:length(changes)
    column = 1;
    for p = 1:size(documentList,2)
        for v = changes(c).valueLow:changes(c).valueStep:changes(c).valueHigh
            documentList(c+1,column) = replaceBetween(documentList(c,p),changes(c).textOrigin, changes(c).textEnd, sprintf('%.6f', v));
            column = column+1;
        end
    end
end

lastRow = size(documentList,1);
%output
for column = 1:size(documentList,2)
    fileID = fopen([file_name, sprintf('%.0f', column), '_generated.xosc'],'w');
    listOfNames(column) = convertCharsToStrings([file_name, sprintf('%.0f', column), '_generated.xosc']);
    doc = documentList(lastRow, column);
    fwrite(fileID,doc{1});
    fclose(fileID);
end

%back to code
cd '..\Code'
end

