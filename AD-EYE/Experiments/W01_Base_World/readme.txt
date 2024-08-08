
                                    ##############
                                    ### README ###
                                    ##############

    - Overview:
This script processes a folder of PCD files filters out lines containing 'NaN' or similar values. 
Then it write the remaining unique lines into a new PCD file. 
The script also allows to customize the rounding precision of the point cloud values (see 'Statistics' section).

    - Usage:
>> Total line number before modification: Total number of lines read from all input files.
>> Total line number after modification: Total number of unique lines written to the new file.
>> Total saving: Difference between the total lines before and after processing.
>> Total NaN: Number of lines containing 'nan' values before filtering.
>> % NaN: Percentage of lines containing 'nan' values before filtering.
>> % Similar lines: Percentage of duplicate lines before filtering.
>> % Total saving: Percentage of lines saved after filtering.

    - Statistics:
------------------------------------------------------------------------------------------------------------------
ROUNDIND to 0 decimal {:.0f} OUTPUT:

##############

Total line number before modification: 1716071
Total line number after modification: 137282
Total saving: 1578789
Total NaN : 439059
Total similar lines: 1139730

##############

% NaN : 25.59%
% Similar lines: 66.42%
% Total saving: 92.00%

##############

SIZE_BEFORE = 61,8MB
SIZE_AFTER = 1,6MB

------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------
ROUNDIND to 1 decimal {:.1f} OUTPUT:

##############

Total line number before modification: 1716071
Total line number after modification: 1133551
Total saving: 582520
Total NaN : 439059
Total similar lines: 143461

##############

% NaN : 25.59%
% Similar lines: 8.36%
% Total saving: 33.94%

##############

SIZE_BEFORE = 61,8MB
SIZE_AFTER = 22,5MB

------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------
ROUNDIND to 2 decimal {:.2f} OUTPUT:

##############

Total line number before modification: 1716071
Total line number after modification: 1276372
Total saving: 439699
Total NaN : 439059
Total similar lines: 640

##############

% NaN : 25.59%
% Similar lines: 0.04%
% Total saving: 25.62%

##############

SIZE_BEFORE = 61,8MB
SIZE_AFTER = 30,5MB

------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------
ROUNDIND to 3 decimal {:.3f} OUTPUT:

##############

Total line number before modification: 1716071
Total line number after modification: 1277010
Total saving: 439061
Total NaN : 439059
Total similar lines: 2

##############

% NaN : 25.59%
% Similar lines: 0.00%
% Total saving: 25.59%

##############

SIZE_BEFORE = 61,8MB
SIZE_AFTER = 35,6MB

------------------------------------------------------------------------------------------------------------------