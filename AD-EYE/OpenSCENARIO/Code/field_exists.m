function exists = field_exists(input_struct,field_to_find)
    %TESTFIELDEXISTANCE Test if the field of a struct exists or not
    exists = false;

    tested_struct = input_struct; % this structure will progress towards the field to be found
    fields = split(field_to_find, '.'); % all the fields that need to exist and need to be checked in order

    for i = 2:length(fields)
        current_searched_field = split(fields(i), ["{",",","}"]);

        if length(current_searched_field) == 1
            if(isfield(tested_struct,fields(i))) % if we can move one step towards the wanted field
                tested_struct = tested_struct.(fields(i)); % we do
                if i == length(fields)
                   exists = true; 
                end
            else
                break
            end
        else
            % check table height and width
            if(isfield(tested_struct,current_searched_field(1)) && size(tested_struct.(current_searched_field(1)),1)>=str2double(current_searched_field(2)) && size(tested_struct.(current_searched_field(1)),2)>=str2double(current_searched_field(3))) % if we can move one step towards the wanted field
                tested_struct = tested_struct.(current_searched_field(1)); % we do
                tested_struct = tested_struct{str2double(current_searched_field(2)),str2double(current_searched_field(3))};
                if i == length(fields)
                   exists = true; 
                end
            else
                break
            end
        end
    end


end

