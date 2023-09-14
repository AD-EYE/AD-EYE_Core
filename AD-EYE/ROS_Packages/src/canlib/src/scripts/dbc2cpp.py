import cantools
import glob
import os
import io

def generateH(db, frame_name):
    output = io.StringIO()

    msg = db.get_message_by_name(frame_name)
    

    output.write('#include "../basic_types.h"\n\n')
    output.write("namespace kcan {\nnamespace dbc {\n\n\n")

    output.write('void {}_Init(\n'
        '    map<uint, string>& frame_ids,\n'
        '    map<std::string, FrameInfo>& frames_info,\n'
        '    map<std::string, SignalGroupInfo>& signalgroups_info,\n'
        '    map<std::string, SignalInfo>& signals_info\n);\n\n'.format(msg.name)
    )


    output.write("\n// Frame\n")
    output.write('const std::string {} {{ "{}" }};\n'.format(msg.name, msg.name))
    output.write("\n")

    output.write("\n// Groups\n")
    for sigg in msg.signal_groups:
        output.write('const std::string {} {{ "{}" }};\n'.format(sigg.name, sigg.name))
    output.write("\n")

    output.write("\n// Signals\n")
    for sig in msg.signals:
        output.write('const std::string {} {{ "{}" }};\n'.format(sig.name, sig.name))
        
    output.write("\n\n}\n}\n")

    with open("./DBC/" + frame_name + ".h", "w") as f:
        f.write(output.getvalue())
    

def generateCpp(db, frame_name):
    signals_output = io.StringIO()
    signal_groups_output = io.StringIO()
    frame_output = io.StringIO()

    msg = db.get_message_by_name(frame_name)
    
    def insertSignal(sig_name, sig_type, parent, parent_type):
        sig = msg.get_signal_by_name(sig_name)
        if sig.byte_order == "big_endian":
            sig_start = (sig.start - sig.length) + 1
            if sig.is_signed:
                sig_start += 16
            else:
                try:
                    if (sig.minimum < 0 and -sig.minimum == sig.maximum and sig.offset == sig.minimum):
                        sig_start += 16
                except:
                    pass
        else:
            sig_start = sig.start

        if sig_start < 0:
            sig_start = -sig_start

        if sig_type == "APP":
            signal_type = "SignalType::APP_SIGNED" if sig.is_signed else "SignalType::APP_UNSIGNED"
        else:
            signal_type = sig_type

        sig_initial = sig.initial if sig.initial else 0

        signals_output.write('    signals_info.insert({{ {name}, {{ {name}, {start}, {length}, {signal_type}, {initial}, {parent}, {parent_type} }} }});\n'
            .format(name=sig.name, start=sig_start, length=sig.length, signal_type=signal_type, initial=sig_initial, parent=parent, parent_type=parent_type))

    ############################################################################################

    checksum_signals = set()
    counter_signals = set()

    for group in msg.signal_groups:
        data_id = checksum_sig = counter_sig = None
        for sig_name in group.signal_names:
            try:
                sig = msg.get_signal_by_name(sig_name)
            except KeyError:
                print(frame_name + ": Problem with signal " + sig_name)
                continue
            try:
                data_id = sig.dbc.attributes["GenSigDataID"].value
                checksum_sig = sig
            except KeyError:
                pass
            
            if sig.name.endswith("ntr") or sig.name.endswith("ounter"):
                counter_sig = sig

        profile_detected = False
        if (checksum_sig or data_id or counter_sig):
            if not (checksum_sig and data_id and counter_sig):
                print("Can't detect profile for frame " + frame_name)
                # print(checksum_sig, data_id, counter_sig)
            else:
                profile_detected = True
                checksum_signals.add(checksum_sig.name)
                counter_signals.add(counter_sig.name)

        if data_id is None:
            data_id = "0x0"
            
        if profile_detected:
            profile_type = "E2EProfileType::P01a" if counter_sig.length == 4 else "E2EProfileType::P05"
            checksum_name=checksum_sig.name
            counter_name=counter_sig.name
        else:
            profile_type = "E2EProfileType::None"
            checksum_name='""'
            counter_name='""'
            
            
        signal_groups_output.write('    signalgroups_info.insert({{ {group_name}, {{ {group_name}, {data_id}, {{ {signal_names} }}, {{ {profile_type}, {checksum_name}, {counter_name} }}, {frame_name} }} }} );\n'.
            format(group_name=group.name,
                    data_id=data_id,
                    signal_names=", ".join(group.signal_names),
                    profile_type=profile_type,
                    checksum_name=checksum_name,
                    counter_name=counter_name,
                    frame_name=msg.name
            )
        )

    #######################################################################################

    msg_signal_names = set(sig.name for sig in msg.signals)
    
    for group in msg.signal_groups:
        for sig_name in group.signal_names:
            try:
                msg_signal_names.remove(sig_name)
                if sig_name in checksum_signals:
                    sig_type = "SignalType::E2E_CHKS"
                elif sig_name in counter_signals:
                    sig_type = "SignalType::E2E_CNTR"
                else:
                    sig_type = "APP"
                insertSignal(sig_name, sig_type, group.name, "ParentType::GROUP")
            except KeyError:
                print(frame_name + ": Problem with signal " + sig_name)
            
    for sig_name in msg_signal_names:
        try:
            if sig_name in checksum_signals:
                sig_type = "SignalType::E2E_CHKS"
            elif sig_name in counter_signals:
                sig_type = "SignalType::E2E_CNTR"
            else:
                sig_type = "APP"
            insertSignal(sig_name, sig_type, frame_name, "ParentType::FRAME")
        except KeyError:
            print(frame_name + ": Problem with signal " + sig_name)

    #############################################################################################

    cycle_time = msg.cycle_time if msg.cycle_time else "0xFFFFFFFF";

    frame_output.write('    frames_info.insert({{ {name}, {{ {name}, {frame_id}, {length}, {period}, {{ {signal_groups} }}, {{ {signals} }} }} }});\n'.
        format(
            name=msg.name,
            frame_id=msg.frame_id,
            length=msg.length,
            period=cycle_time,
            signal_groups=", ".join(g.name for g in msg.signal_groups),
            signals=", ".join(msg_signal_names)
        ))
    
    frame_output.write('\n    frame_ids.insert({{ {}, {} }});'.format(msg.frame_id, msg.name))

    #######################################################################################

    with open("./DBC/" + frame_name + ".cpp", "w") as f:
        f.write('#include "{}.h"\n\n\n'.format(msg.name))
        f.write("namespace kcan {\nnamespace dbc {\n\n\n")
        f.write('void {}_Init(\n'
            '    map<uint, string>& frame_ids,\n'
            '    map<std::string, FrameInfo>& frames_info,\n'
            '    map<std::string, SignalGroupInfo>& signalgroups_info,\n'
            '    map<std::string, SignalInfo>& signals_info\n) {{\n'.format(msg.name)
        )

        f.write(signals_output.getvalue())
        f.write("\n")
        f.write(signal_groups_output.getvalue())
        f.write("\n")
        f.write(frame_output.getvalue())
        f.write("\n}\n\n\n}\n}\n")


for dbc_file in glob.glob("*.dbc"):
    db = cantools.database.load_file(dbc_file)
    for frame in db.messages:
        try:
            generateH(db, frame.name)
        except Exception:
            print("Not generated: " + frame.name)
            continue
        try:
            generateCpp(db, frame.name)
        except Exception:
            print("Not generated: " + frame.name)
            os.remove("./DBC/" + frame.name + ".h")
            continue
