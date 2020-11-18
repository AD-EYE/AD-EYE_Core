function field = get_field(input_struct,field_to_find)


    tested_struct = input_struct; % this structure will progress towards the field to be found
    fields = split(field_to_find, '.'); % all the fields that need to exist and need to be checked in order

    for i = 2:length(fields)
        current_searched_field = split(fields(i), ["{",",","}"]);

        if length(current_searched_field) == 1
            tested_struct = tested_struct.(fields(i));
        else
            if(length(tested_struct.(current_searched_field(1)))==1)
                tested_struct = tested_struct.(current_searched_field(1));
            else
                tested_struct = tested_struct.(current_searched_field(1));
                tested_struct = tested_struct{str2double(current_searched_field(2)),str2double(current_searched_field(3))};
            end
        end
    end
    field = tested_struct;
end

