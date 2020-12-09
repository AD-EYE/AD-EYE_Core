function MonteCarloTA(TAOrderFile, nb_monte_carlo_samples)
    originalTAOrder = readtable(TAOrderFile, 'ReadRowNames',true,'ReadVariableNames',false);
    
    
    indexes = randi([1 width(originalTAOrder)],1,nb_monte_carlo_samples);
    
    sampledTAOrder = table('Size', [7 nb_monte_carlo_samples], 'VariableTypes', repelem("string", nb_monte_carlo_samples), 'RowNames', {'FolderExpName' 'PrescanExpName' 'EgoName' 'AutowareConfig' 'SimulinkConfig' 'TagsConfig' 'SHHConfig'});

    
    for i=1:length(indexes)
        sampledTAOrder{'FolderExpName',i} = originalTAOrder{'FolderExpName',indexes(i)};
        sampledTAOrder{'PrescanExpName',i} = originalTAOrder{'PrescanExpName',indexes(i)};
        sampledTAOrder{'EgoName',i} = originalTAOrder{'EgoName',indexes(i)};
        sampledTAOrder{'AutowareConfig',i} = originalTAOrder{'AutowareConfig',indexes(i)};
        sampledTAOrder{'SimulinkConfig',i} = originalTAOrder{'SimulinkConfig',indexes(i)};
        sampledTAOrder{'TagsConfig',i} = originalTAOrder{'TagsConfig',indexes(i)};
        sampledTAOrder{'SHHConfig',i} = originalTAOrder{'SHHConfig',indexes(i)};
    end
    
    cd('Configurations')
    delete('TAOrder_Monte_Carlo.xlsx') % to overwrite the preexisting file, without this line overlaps can occur if the previous table was bigger
    writetable(sampledTAOrder, 'TAOrder_Monte_Carlo.xlsx', 'WriteRowNames', true, 'WriteVariableNames', false);
    cd('..')
    
end
