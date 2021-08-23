function listOfNames2 = OpenScenarioMod2(fileName)
%go to correct folder
cd '..\OpenSCENARIO_experiments'

fileID = fopen([fileName, '.xosc']);
document = fscanf(fileID, '%c');
fclose(fileID);

%search for the array, array of form {x,y,z}
findOpen = strfind(document, '{');
findClose = strfind(document, '}');
%findSeparator = strfind(document, ',');

if isempty(findOpen)
    listOfNames2(1) = convertCharsToStrings([fileName, '.xosc']);
    cd '..\Code';
    return
end

for c = 1:length(findOpen)
    changes(c).textOrigin = findOpen(c);
    %changes(c).textBrake1 = findSeparator(2*c-1);
    %changes(c).textBrake2 = findSeparator(2*c);
    changes(c).textEnd = findClose(c);
    text = extractBetween(document,  findOpen(c)+1,  findClose(c)-1)
    findSeparator = strfind(text, ',');
    if not(isempty(findSeparator{1,1}))
        findSeparator = findSeparator{1,1};
        changes(c).valueLow = str2double(extractBetween(document, changes(c).textOrigin+1, changes(c).textOrigin-1+findSeparator(1)));
        changes(c).valueStep = str2double(extractBetween(document, changes(c).textOrigin+1+findSeparator(1), changes(c).textOrigin-1+findSeparator(2)));
        changes(c).valueHigh = str2double(extractBetween(document, changes(c).textOrigin+1+findSeparator(2), changes(c).textEnd-1));
    else
        findSeparator = strfind(text, ';');
        findSeparator = findSeparator{1,1};
        values=[];
        for i= 1:length(findSeparator)+1
            if i==1
                values = [values,str2double(extractBetween(document, changes(c).textOrigin+1, changes(c).textOrigin-1+findSeparator(1)))];
            end
            if i>1 && i<length(findSeparator)+1
                values = [values,str2double(extractBetween(document, changes(c).textOrigin+1+findSeparator(i-1), changes(c).textOrigin-1+findSeparator(i)))];
            end
            if i== length(findSeparator)+1
                values = [values,str2double(extractBetween(document, changes(c).textOrigin+1+findSeparator(i-1), changes(c).textEnd-1))];
            end
        end
    end
end

%copy document
documentList(1,1)={document};

%change document
for c = 1:length(changes)
    colum = 1;
    for p = 1:size(documentList,2)
        findOpen = strfind(documentList{c,1}, '{');
        findClose = strfind(documentList{c,1}, '}');
        findSeparator = strfind(text, ',');
        if (isempty(findSeparator{1,1}) || (isempty(changes(c).valueLow)  && isempty(changes(c).valueStep) && isempty(changes(c).valueHigh) ))
            for v= 1:length(values)
                documentList(c+1,colum) = replaceBetween(documentList(c,p),findOpen(1), findClose(1), sprintf('%.6f', values(v)));
                colum = colum+1;
            end
        else
            for v = changes(c).valueLow:changes(c).valueStep:changes(c).valueHigh
                documentList(c+1,colum) = replaceBetween(documentList(c,p),findOpen(1), findClose(1), sprintf('%.6f', v));
                colum = colum+1;
            end
        end
    end
end

lastRow = size(documentList,1);
%output
for colum = 1:size(documentList,2)
    fileID = fopen([fileName, sprintf('%.0f', colum), '_generated.xosc'],'w');
    listOfNames2(colum) = convertCharsToStrings([fileName, sprintf('%.0f', colum), '_generated.xosc']);
    doc = documentList(lastRow, colum);
    fwrite(fileID,doc{1});
    fclose(fileID);
end

%back to code
cd '..\Code'
end

