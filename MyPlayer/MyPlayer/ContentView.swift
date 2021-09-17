//
//  ContentView.swift
//  MyPlayer
//
//  Created by 程倩的MacBook on 2021/9/2.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        Button("点击我") {
            print("点击事件")
            print("\n")
            printHellow();
            print("\n")
            let person = create();
            printPersonInfo(person);
            
        }.frame(width: 500, height: 400, alignment: Alignment.center)
    }
}


struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
