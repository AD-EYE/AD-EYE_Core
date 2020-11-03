function TACombinations(ExpNameArray, AutowareExpNameArray, EgoNameArray, AutowareConfigArray, GoalConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)
if not((length(ExpNameArray) == length(AutowareExpNameArray)) && (length(ExpNameArray) == length(EgoNameArray)))
    error('Error: ExpNameArray, AutowareExpNameArray and EgoNameArray must have the same length.')
end

%ExpNameArray = ["e1" "e2"];
%AutowareExpNameArray = ["a1" "a2"];
%EgoNameArray = ["Ego" "Ego"];
%AutowareConfigArray = ["ac1" "ac2" "ac3"];
%GoalConfigArray = ["g1" "g2"];
%SimulinkConfigArray = ["sc1" "sc2"];
%TagsConfigArray = ["t1" "t2"];
%SHHConfig = "ssh";

numberOfColums = length(ExpNameArray)*length(AutowareConfigArray)*length(GoalConfigArray)*length(SimulinkConfigArray)*length(TagsConfigArray);

TAOrder = table('Size', [8 numberOfColums], 'VariableTypes', repelem("string", numberOfColums), 'RowNames', {'ExpName' 'AutowareExpName' 'EgoName' 'AutowareConfig' 'GoalConfig' 'SimulinkConfig' 'TagsConfig' 'SHHConfig'});

c=1;
for C_Sce = 1:length(ExpNameArray)
    for C_Aut = 1:length(AutowareConfigArray)
        for C_goa = 1:length(GoalConfigArray)
            for C_Sim = 1:length(SimulinkConfigArray)
                for C_Tag = 1:length(TagsConfigArray)
                    TAOrder{'ExpName',c} = ExpNameArray(C_Sce);
                    TAOrder{'AutowareExpName',c} = AutowareExpNameArray(C_Sce);
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
writetable(TAOrder, 'TAOrder.csv', 'WriteRowNames', true, 'WriteVariableNames', false);
cd('..')

end


