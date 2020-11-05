function TACombinations(FolderExpNameArray, PrescanExpNameArray, EgoNameArray, AutowareConfigArray, GoalConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)
if not((length(FolderExpNameArray) == length(PrescanExpNameArray)) && (length(FolderExpNameArray) == length(EgoNameArray)))
    error('Error: FolderExpNameArray, PrescanExpNameArray and EgoNameArray must have the same length.')
end


numberOfColums = length(FolderExpNameArray)*length(AutowareConfigArray)*length(GoalConfigArray)*length(SimulinkConfigArray)*length(TagsConfigArray);

TAOrder = table('Size', [8 numberOfColums], 'VariableTypes', repelem("string", numberOfColums), 'RowNames', {'FolderExpName' 'PrescanExpName' 'EgoName' 'AutowareConfig' 'GoalConfig' 'SimulinkConfig' 'TagsConfig' 'SHHConfig'});

c=1;
for C_Sce = 1:length(FolderExpNameArray)
    for C_Aut = 1:length(AutowareConfigArray)
        for C_goa = 1:length(GoalConfigArray)
            for C_Sim = 1:length(SimulinkConfigArray)
                for C_Tag = 1:length(TagsConfigArray)
                    TAOrder{'FolderExpName',c} = FolderExpNameArray(C_Sce);
                    TAOrder{'PrescanExpName',c} = PrescanExpNameArray(C_Sce);
                    TAOrder{'EgoName',c} = EgoNameArray(C_Sce);
                    TAOrder{'AutowareConfig',c} = AutowareConfigArray(C_Aut);
                    TAOrder{'GoalConfig',c} = GoalConfigArray(C_goa);
                    TAOrder{'SimulinkConfig',c} = SimulinkConfigArray(C_Sim);
                    TAOrder{'TagsConfig',c} = TagsConfigArray(C_Tag);
                    TAOrder{'SHHConfig',c} = SHHConfig;
                    
                    c=c+1;
                end
            end
        end
    end
end

cd('Configurations')
writetable(TAOrder, 'TAOrder.xlsx', 'WriteRowNames', true, 'WriteVariableNames', false);
cd('..')

end


